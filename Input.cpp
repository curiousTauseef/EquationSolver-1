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
		return (char_ == '+' || char_ == '-' || char_ == '=');
	};

	// Prepend + Symbol
	auto prependplus = [&] ()
	{
		if (!isseparatingoperator(input.front()))
			input.insert(0, 1, '+');
	};
	
	prependplus();

	// Split Input String into _expression vector while keeping preceeding separating operators
	auto found = input.begin();
	auto* current_container = &obj_._left_expressions;
	while (found != input.end())
	{
		// Switch container
		if (input.front() == '=')
		{
			current_container = &obj_._right_expressions;
			input.erase(0, 1);
			prependplus();
		}

		found = std::find_if(input.begin() + 1, input.end(), isseparatingoperator);
		current_container->emplace_back(input.begin(), found);
		input.erase(input.begin(), found);
		found = input.begin();
	}

	return is_;
}
