#include <vector>
#include <sstream>

template<typename T>
class rpn_templ
{
	std::vector<T> stack;
	T tmp;
	T evaluate_postfix(const char operation)
	{

		T left, right, result;

		//Pull out top two elements
		right = stack.back();
		stack.pop_back();
		left = stack.back();
		stack.pop_back();
		// Perform the maths
		switch (operation)
		{
		case '+': result = left + right; break;
		case '-': result = left - right; break;
		case '*': result = left * right; break;
		case '/': {
			if (static_cast<double>(right) == 0) {
				// TODO exception
			}
			else
			{
				result = left / right;
			}
			break;
		}
		case 'm': result = std::min(left, right);break;

		}

		stack.push_back(result);

		return stack[0]; //last element is the answer
	};

	void print_stack()
	{
		for (int n = 0; n < stack.size(); n++) {
			std::cout << '\t' << n << ". " << stack[n] << std::endl;
		}
	}
public:
	rpn_templ() {};
	~rpn_templ() {};
	void run() {
		std::cout << " --------------------------\n| Simple RPN Calculator\n--------------------------\n\t'n <number>' to put a number on the stack'\n\t'<opertation>' to du an operation on the stack\n\t 'd' to delete a number from the stack\n\t 'q' to quit the calculator" << std::endl;
		std::string line, s;

		do {
			std::cout << "Command: ";
			std::getline(std::cin, line);

			std::stringstream ss(line);
			ss >> s;

			if (s.length() > 1) {
				std::cout << "ERROR: command too long, try again!" << std::endl;
			}
			else
			{

				switch (s[0])
				{
					case 'q': break;

					case 'd':
						tmp = stack.back();
						stack.pop_back();
						print_stack();
						break;
					case '+':
						evaluate_postfix(s[0]);
						print_stack();
						break;
					case '-':
						evaluate_postfix(s[0]);
						print_stack();
						break;
					case '*':
						evaluate_postfix(s[0]);
						print_stack();
						break;
					case '/':
						evaluate_postfix(s[0]);
						print_stack();
						break;
					case 'm':
						evaluate_postfix(s[0]);
						print_stack();
						break;
					case 'n':
						ss >> tmp;
						stack.push_back(tmp);
						print_stack();
						break;
					default:
						std::cout << "ERROR: unknown command, try again!" << std::endl;
						break;
					}
			}
		} while (s != "q");
	};
};