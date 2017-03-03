#include "Input.hpp"

std::istream& operator>>(std::istream& is_, Input& obj_)
{
	// IStream to String
	std::string input;
	is_ >> input;

	// Remove spaces
	std::remove_if(input.begin(), input.end(), isspace);

	// Find out if character is separating opeator (+/-)
	auto isseparatingoperator = [] (const char char_)
	{
		return (char_ == '+' || char_ == '-');
	};

	// Prepend + Symbol
	if (!isseparatingoperator(input.front()))
		input.insert(0, 1, '+');

	// Split Input String into _expression vector while keeping preceeding separating operators
	auto found = input.begin();
	while (found != input.end())
	{
		found = std::find_if(input.begin() + 1, input.end(), isseparatingoperator);

		obj_._left_expressions.emplace_back(input.begin(), found);
		input.erase(input.begin(), found);
		found = input.begin();
	}

	return is_;
}
