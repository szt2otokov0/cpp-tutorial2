// Stl_data.cpp : Defines the entry point for the application.
//

#include "Stl_data.h"

#include <vector>

#include "string"
#include "fstream"

using namespace std;

class file_reader
{
public:
	explicit file_reader(const string& filename)
	{
		file_ = make_unique<ifstream>(filename.c_str());
		if (!file_->is_open()) throw runtime_error("Failed to open file");
	}

	string read_all() const
	{
		string content;
		file_->seekg(0, ios::end);
		content.resize(file_->tellg());
		file_->seekg(0, ios::beg);
		file_->read(const_cast<char*>(content.c_str()), static_cast<long>(content.size()));
		return content;
	}
private:
	unique_ptr<ifstream> file_;
};


int main()
{
	const file_reader reader("../../../tut_prompt.txt");
	const string file_text = reader.read_all();
	cout << file_text << '\n';
	std::vector<char*> paragraphs;
	unique_ptr<char> line;
	int size = 0;
	for (const char i : file_text)
	{
		cout << i;
		if (i == '\n')
		{
			paragraphs.push_back(line.get());
			size = 0;
			line = make_unique<char>(0);
		}
		else {
			auto new_line = make_unique<char>(size + 1);
			for (int j = 0; j < size; j++)
			{
				new_line.get()[j] = line.get()[j];
			}
			new_line.get()[size] = i;
			line = std::move(new_line);
			size++;
		}
	}

	for (const char* i : paragraphs)
	{
		cout << i << "hey, this is from the list!" << '\n';
	}


	char b;

	cin >> b;
	return 0;
}
