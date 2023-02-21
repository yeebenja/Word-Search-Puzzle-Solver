# Word Search Puzzle Solver
⭐Given a board of letters and a word bank, tile coordinates of each word from the word bank are calculated and reported to the user.

<img width="461" alt="image" src="https://user-images.githubusercontent.com/95982168/210907444-d65631ec-e7ce-49a7-8751-7de524d28b4e.png">

<img width="429" alt="image" src="https://user-images.githubusercontent.com/95982168/210911203-42797e85-fe21-4b49-be84-fd593dae5ebd.png">

![Word_search_solver_demo_Chinese_New_Year](https://user-images.githubusercontent.com/95982168/210911020-c314ef80-b369-4562-b107-618f4696f94d.gif)

After "word_search_puzzle_solver.cpp" compiling, command line arguments must be included. Following the executable, the board .txt file and word bank .txt file are passed into main. In this example, "[executable] chinese_new_year_board.txt chinese_new_year_word_bank.txt" was called.

<img width="190" alt="image" src="https://user-images.githubusercontent.com/95982168/210908961-eb6f9fa2-d51e-44ed-906f-0245394ea2a4.png">

In the board .txt file, the width and height of the word search board must be specified above the board text. In this example, the word search puzzle was 15 by 15.

<img width="208" alt="image" src="https://user-images.githubusercontent.com/95982168/210909067-3b740a58-91ef-49e4-b497-29b6a109cef3.png">

Lowercase and uppercase letters do not cause an issue inside both input files, although, results will print found words in uppercase letters for readability, as seen above.

⭐Included in the folder are some sample word search boards and word banks. The file "word_bank_3.txt" contains all words that are acceptable in Scrabble, so if you want to find every single possible word in the word search use "word_bank_3.txt" as your word bank. Enjoy! 😆

⭐Fun Fact: Palindrome words are found twice!

⭐Aside: After taking my Data Structures and Algorithms course, I've realized that my implementation for this tool is highly inefficient. I should try to redo this project some other time. 😁
