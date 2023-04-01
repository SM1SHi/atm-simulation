#include <iostream>
#include <chrono>
#include <future>

#include "utils.h"

//int main() {
//    
//    const int TIME_LIMIT = 10;
//
//    std::promise<void> promiseObj;
//    std::future<void> futureObj = promiseObj.get_future();
//
//    auto start = std::chrono::system_clock::now();
//    //remember to have exit(0) in this function or it will just run until the counter reaches TIME_LIMIT, the better solution is more complicated
//    std::thread threadObj(&usrinputStats);
//
//    // wait for the function to complete or the timer to expire
//    std::future_status status = futureObj.wait_for(std::chrono::seconds(TIME_LIMIT));
//    if (status == std::future_status::timeout) {
//        // time limit has been reached, terminate the program
//        std::cout << "Time limit reached" << std::endl;
//        threadObj.detach();
//        std::exit(0);
//    }
//
//    auto end = std::chrono::system_clock::now();
//    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
//    std::cout << "Elapsed time: " << elapsed_seconds << " seconds" << std::endl;
//
//    threadObj.join();
//
//    return 0;
//}
int main() {
	std::string loginID = confirmID();
	authenticateUser(loginID);
	
}