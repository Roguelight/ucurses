#include <command/Callback.hpp>
#include <fstream>

using namespace std;

namespace ucurses { 

	CallbackStack::CallbackStack(size_t size)
	{
		stack_array.reserve(size);
	}

	void CallbackStack::Emplace(int key, std::function<void()> callback)
	{
		stack_array.emplace_back(key, callback,string(""));
	}

	void CallbackStack::Process(int key)
	{
		if (!stack_array.empty())
		{
			if (stack_array.back().command == key)
			{
				stack_array.back().command.execute();
				stack_array.pop_back();
			}
		}
	}

	void CallbackStack::Execute()
	{
		stack_array.back().command.execute();
		stack_array.pop_back();
	}

    void CallbackStack::write_form(std::ostream& stream) const
    {
        stream << "<Size> " << stack_array.size() << std::endl;
    }
	
	std::string CallbackStack::getTip() const
	{
		if (!stack_array.empty())
			return stack_array.back().tip;
		else
			return string("");
	}

	void CallbackStack::setTip(const std::string& inTip)
	{
		if (!stack_array.empty())
			stack_array.back().tip = inTip;
	}

}
