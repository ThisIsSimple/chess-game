#include <iostream>

namespace chess
{
	namespace answer
	{
		void MainMenu(std::istream& is, std::ostream& os);
		
		void PrintInitialBoard(std::ostream& os);
		
		void LoadBoard(std::istream& is, std::ostream& os);
		
		void PrintGameInformation(std::istream& is, std::ostream& os);
	}
}
