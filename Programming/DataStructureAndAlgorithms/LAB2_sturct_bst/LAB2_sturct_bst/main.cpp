#include "files.h"
#include "bst.h"
#include <memory>

using namespace std;
constexpr auto PATH = "C:\\Users\\Владислав\\source\\repos\\LAB2_sturct_bst\\LAB2_sturct_bst\\treemap";
constexpr auto EXTENSION = ".txt";


int main(const int argc, const char* argv[])
{
	try {
		auto files = make_unique<dirfile>(PATH, EXTENSION);
		files->menu();
		auto tree = bst<int>();
		while (!files->from.eof())
		{
			int x;
			files->from >> x;
			tree.add_node(x);
		}
		files.reset();
		
		cout << "Tree:" << endl;
		tree.print_visual();
		cout << "Preorder:" << endl;
		tree.print_preorder();
		cout << "Inorder:" << endl;
		tree.print_inorder();
		cout << "Postorder:" << endl;
		tree.print_postorder();
		cout << "On levels:" << endl;
		tree.print_onlevel();
		cout << "Copy test:" << endl;
		{
			auto tree_copy = bst<int>(tree);
			tree_copy.print_visual();
		}
		cout << (tree.balanced()==true? "Balanced" : "Not balanced") << endl;
		cin.get();
		return 0;
	}
	catch (Myexception &e)
	{
		cout << e.GetName() << endl;
		cout << "Press any key to continue" << endl;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cin.get();
		return e.GetVal();
	};
}