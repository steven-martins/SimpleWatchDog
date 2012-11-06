#include <iostream>
#include <string>
#include "Checker.h"
#include "Scheduler.h"
 

int main(int ac, char *av[])
{
	// Lire fichier de conf
	// G�n�rer les checks
	//   -> ip, port � tester
	//   -> Action � effectuer
	//   -> Dur�e entre chaque check
	// Scheduler
	//   -> loop sur les taches a effectuer
	//       -> si temps est d�pass� -> on lance le check et on met � jour le (next) timestamp
	Checker c("127.0.0.1", 80,	"echo toto", 10);
	Scheduler s;
	s.pushChecker(c);
	s.pushChecker(Checker("127.0.0.1", 443, "echo tutu", 21));
	s.run();
	system("PAUSE");
}
