# password-gen
# Advanced Password Generator

## Overview
This project is an advanced password generator written in C++. It provides users with the ability to create strong and secure passwords using a variety of character sets, including uppercase letters, lowercase letters, digits, special characters, Greek, and Cyrillic characters. It also features password strength analysis, brute-force time estimation, password masking, and history management.

## Features
- **Customizable Password Generation**: Allows users to specify the length and character sets for passwords.
- **Entropy Calculation**: Estimates password strength based on entropy.
- **Brute-Force Time Estimation**: Predicts the time required to crack a password using brute-force attacks.
- **Password Complexity Check**: Detects common weak patterns like "123" or repetitive characters.
- **Password Masking**: Masks passwords for secure display.
- **Password History Management**: Saves and loads previously generated passwords.
- **Multi-threaded Generation Simulation**: Simulates password generation using multi-threading.
- **QR Code Generation**: Generates QR codes for passwords (future enhancement).
- **Export to CSV**: Allows exporting password history to a CSV file.
- **Phonetic Mnemonics**: Generates phonetic mnemonic representations of passwords.

## Dependencies
This project uses standard C++ libraries, so no additional dependencies are required.

## Installation and Usage
1. **Compile the program**:
   ```sh
   g++ -o password_generator password_generator.cpp -std=c++11
   ```
2. **Run the executable**:
   ```sh
   ./password_generator
   ```
3. **Follow the on-screen menu** to generate and manage passwords.

## Functions
### Password Generation
- Generates passwords of custom length with various character sets.
- Ensures at least one character from each selected set is included.

### Security Analysis
- **Entropy Calculation**: Uses logarithmic calculations to measure password randomness.
- **Complexity Check**: Detects weak passwords with common patterns.
- **Brute-force Time Estimation**: Estimates how long it would take to crack the password.

### Password Management
- **Save Passwords**: Stores passwords in a file.
- **Load Password History**: Retrieves previously generated passwords.
- **View Password History**: Displays past passwords.
- **Export to CSV**: Saves password history to a CSV file.

### Utility Functions
- **Mask Passwords**: Masks passwords when displaying them.
- **Generate Phonetic Mnemonic**: Converts passwords into a more memorable format.
- **Generate Random PIN**: Creates a numeric PIN of a given length.
- **Dictionary Check**: Verifies if a password exists in a common password dictionary.

## Future Enhancements
- Implement QR code generation for easy sharing.
- Improve dictionary-based password strength evaluation.
- Add UI for a better user experience.

## License
This project is open-source and free to use under the MIT License.

## Author
Developed by FURKAN ASKIN 

