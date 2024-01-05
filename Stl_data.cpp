// Stl_data.cpp : Defines the entry point for the application.
//

#include "Stl_data.h"
#include "string"
#include "fstream"

using namespace std;

class file_reader
{
public:
	explicit file_reader(const string& filename)
	{
		file_ = make_unique<ifstream>(filename.c_str());
		if(!file_->is_open()) throw runtime_error("Failed to open file");
	}

	string read_all() const
	{
		string content;
		file_->seekg(0,ios::end);
		content.resize(file_->tellg());
		file_->seekg(0,ios::beg);
		file_->read(const_cast<char*>(content.c_str()),static_cast<long>(content.size()));
		return content;
	}
private:
	unique_ptr<ifstream> file_;
};


int main()
{
	const file_reader reader("../../../tut_prompt.txt");
	cout << reader.read_all() << '\n';

	char b;

	cin >> b;
	return 0;
}
