#ifndef INPUT_HPP
#define INPUT_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <istream>
#include <algorithm>

class Input
{
	public:
		friend std::istream&		operator>>(std::istream& is_, Input& obj_);

private:
		bool						isSeparatingOperator(const char& char_);
		void						splitInput();
		void						prependPlus();
private:
		std::vector<std::string>	_left_expressions;
		std::vector<std::string>	_right_expressions;
		std::string					_input;
};

#endif // INPUT_HPP