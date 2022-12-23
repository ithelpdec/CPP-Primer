// Exercise 17.12:
/*
 Using the data structure from the previous question, write a function that takes a question number and a value to indicate a true/false answer and updates the quiz results accordingly.
 
 >> Did this wihtout realising in the last question.
 
 >> Decided to split it into two functions instead of one.
 >> More clearly sets answers to true or false
 
*/

#include <bitset>
#include <iostream>

template <std::size_t N> struct Quiz {
    std::bitset<N> quiz;
    
    // we could also do the following:
    // std::bitset<10> quiz;
    // std::bitset<100> quiz;
    
    void markAsTrue_Question(int n)  { quiz.set(n - 1); }
    void markAsFalse_Question(int n) { quiz.reset(n - 1); }
    
    int answerToQuestion(int n)      { return quiz[n - 1]; }
};

// added printResults() template function to tidy main() function
template <std::size_t N> void printResults(const Quiz<N> &candidate) {
    for (int i = 0; i != candidate.quiz.size(); ++i) {
        std::cout << i + 1 << ": " << (candidate.quiz[i] ? "True" : "False") << std::endl;;
    } std::cout << std::endl;
}

int main()
{
    Quiz<10> candidate1;
    
    candidate1.markAsTrue_Question(10);
    std::cout << "Setting question 10 to \"True\"...\n";
    std::cout << "Candidate 1's answers: " << candidate1.quiz << "\n" << std::endl;
    
    std::cout << "Candidate 1's answer to question 10: "
              << (candidate1.answerToQuestion(10) ? "True" : "False") << "\n" << std::endl;
    
    candidate1.markAsFalse_Question(10);
    std::cout << "Setting question 10 to \"False\"...\n";
    std::cout << "Candidate 1's answers: " << candidate1.quiz << "\n" << std::endl;
    
    // another way to view answers using for loop
    std::cout << "Candidate 1's answers: " << std::endl;
    printResults(candidate1);
    
    Quiz<100> candidate2;
    std::cout << "Candidate 2's answers: " << std::endl;
    printResults(candidate2);
}
