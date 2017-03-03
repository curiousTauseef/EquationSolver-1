#include "Input.hpp"

// Split Input String into _expression vector while keeping preceding separating operators
void Input::splitInput()
{
	auto found = _input.begin();
	auto* current_container = &_left_expressions;
	while (found != _input.end())
	{
		// Switch container
		if (_input.front() == '=')
		{
			current_container = &_right_expressions;
			_input.erase(0, 1);
			prependPlus();
		}

		found = std::find_if(_input.begin() + 1, _input.end(), [&](const char& char_)
		{
			return isSeparatingOperator(char_);
		});

		current_container->emplace_back(_input.begin(), found);
		_input.erase(_input.begin(), found);
		found = _input.begin();
	}
}

// Put a + in front of the _input string if necessary
void Input::prependPlus()
{
	if (!isSeparatingOperator(_input.front()))
		_input.insert(0, 1, '+');
}

// Find out if character is separating operator in the front of the input (+/-)
bool Input::isSeparatingOperator(const char& char_)
{
	return (char_ == '+' || char_ == '-' || char_ == '=');
}

std::istream& operator>>(std::istream& is_, Input& obj_)
{
	// Create Shorthand
	auto& input = obj_._input;

	// IStream to String
	is_ >> input;

	// Remove spaces
	std::remove_if(input.begin(), input.end(), isspace);

	// Prepend + Symbol
	obj_.prependPlus();

	obj_.splitInput();

	return is_;
}
