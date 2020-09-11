#include "file_func.h"
#include "graph.h"
#include <memory>



using namespace std;
/* ERROR LOG:
1 - workdir is empthy
2 - bad structure of file
3 - error to open file
4 - graphs erros
*/


template<class T>
void cin_clear(T &x);

constexpr auto PATH = "C:\\Users\\Владислав\\source\\repos\\LAB2_struct_graph\\LAB2_struct_graph\\graphs";
constexpr auto EXTENSION = ".txt";


enum TYPE { ADJACENCY_MATRIX ,TRIANGLE_MATRIX, ADJACENCY_LIST };

int main(int argc, char* argv[])
{
	try 
	{
		bool quit = true;
		auto files = make_shared<dirfile>(PATH, EXTENSION); //new dirfile(PATH, EXTENSION);
		enum TYPE init;
		shared_ptr<Graph> graph;

		files->menu();
		{

			char ch_type = files->read_type();
			if (ch_type == 't' || ch_type == 'T')
				init = TRIANGLE_MATRIX;
			else if (ch_type == 'l' || ch_type == 'L')
				init = ADJACENCY_LIST;
			else if (ch_type == 'm' || ch_type == 'M')
				init = ADJACENCY_MATRIX;
			else if (ch_type == 'f' || ch_type == 'F') { //if was opened a FAQ file program will close
				files->read_whole();
				cout << "Press any key to continue" << endl;
				std::cin.clear(); std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); std::cin.get();
				return 0;
			}
			else throw Myexception("Wrong structure of txt file\nReduct and try again!", 2);
		}
		size_t towns = files->count_town();
		if (towns < 1) throw Myexception("Not enough towns", 2); 

		if (init == ADJACENCY_MATRIX)
			graph = make_unique<MatrixNeoGraph>(towns);
		else if (init == TRIANGLE_MATRIX)
			graph = make_unique<TriangleMatrixNeoGraph>(towns);
		else
			graph = make_unique<ListNeoGraph>(towns);

		while (!files->from.eof())
		{
			if (files->read_road()) { 
				if (files->road_type()) // first type of roads
					graph->add_path(files->road_data.from, files->road_data.width, files->road_data.to);
				else // second type
					graph->add_path(files->road_data.from, files->road_data.width, files->road_data.to, 1);
			}
		}
		files.reset(); //reset files coz dirfile obj is not needed anymore
		graph->print_d();
		char answer = 48;
		bool floyd_fl = true;
		size_t dijkastra_fl=numeric_limits<size_t>::max(); //size_t is unsigned type, so we can just put in var 0 or -value
		while (answer != 'n' && answer != 'N')				//to minimize a coincidence with A(town num) variable
		{
			size_t A = 0, B = 0;
			do {
				cout << "Type Origin: ";
				cin_clear(A);
				cout << "Type Destination: ";
				cin_clear(B);
				if (A == B || A > towns || B > towns)
					cout << "Wrong input!" << endl;
				else break;
			} while (true);
			A--;	B--;
			if (init == ADJACENCY_MATRIX)
			{
				if (floyd_fl)
				{
					((MatrixNeoGraph*)&(*graph))->floyd_find();
				    {
						cout << endl;
						for (int i = -33; i < 0; i++)
							cout << static_cast<char>(-78);
						cout << endl;
						cout << static_cast<char>(-78) << "\t After algorithm \t" << static_cast<char>(-78) << endl;
						for (int i = -33; i < 0; i++)
							cout << static_cast<char>(-78);
						cout << endl;
						graph->print_d();

					}
					floyd_fl = false;
				}
				((MatrixNeoGraph*)&(*graph))->restore(A,B);

			}
			else if (init == TRIANGLE_MATRIX) {
				if (floyd_fl)  //for make floyd warshall algorithm work once
				{
					((TriangleMatrixNeoGraph*)&(*graph))->floyd_find();
					{
						cout << endl;
						for (int i = -33; i < 0; i++)
							cout << static_cast<char>(-78);
						cout << endl;
						cout << static_cast<char>(-78) << "\t After algorithm \t" << static_cast<char>(-78) << endl;
						for (int i = -33; i < 0; i++)
							cout << static_cast<char>(-78);
						cout << endl;
						graph->print_d();

					}
					floyd_fl = false;
				}
				((TriangleMatrixNeoGraph*)&(*graph))->restore(A, B);
			}
			else {
				if (A!=dijkastra_fl) { //if node will be the same its not necessary to use dijkstra algorithm one more time
					((ListNeoGraph*) & (*graph))->dijkstra_find(A);
					dijkastra_fl = A;
				}
				((ListNeoGraph*)& (*graph))->restore(A, B);
			}
			cout << "Do u want to find another journey?(y/n)" << endl;
			while ((cin >> answer) && !(answer == 'y' || answer == 'Y' || answer == 'n' || answer == 'N'));
		}
		std::cin.clear(); std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); std::cin.get();
		return 0;
	}
	catch (Myexception& e)
	{
		cout << e.GetName() << endl;
		cout << "Press any key to continue" << endl;
		std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cin.get();
		return e.GetVal();
	};
}

template<class T>
void cin_clear(T &x)
{
	while (!(cin >> x))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cerr << "Wrong input!" << endl;
	}
}

