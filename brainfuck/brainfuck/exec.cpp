// 
// Interpiler - turn an interpreter into a compiler
// Brainfuck example
// Copyright (C) 2015  Félix Cloutier
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// 

#include "exec.h"

using namespace std;

namespace brainfuck
{
	void to_executable_visitor::visit(inst& inst)
	{
		executable.emplace_back(inst.opcode);
	}
	
	void to_executable_visitor::visit(scope& scope)
	{
		for (auto& statement : scope.statements)
		{
			visit(*statement);
		}
	}
	
	void to_executable_visitor::visit(loop& loop)
	{
		size_t start_index = executable.size();
		executable.emplace_back(opcode::loop_enter);
		visit(*loop.body);
		size_t end_index = executable.size();
		executable.emplace_back(opcode::loop_exit);
		
		unsigned u_start_index = static_cast<unsigned>(start_index);
		unsigned u_end_index = static_cast<unsigned>(end_index);
		if (u_start_index != start_index || u_end_index != end_index)
		{
			throw invalid_argument("program too large");
		}
		
		executable[start_index].data = u_end_index + 1;
		executable[end_index].data = u_start_index + 1;
	}
	
	vector<executable_statement> to_executable_visitor::code()
	{
		vector<executable_statement> temp;
		executable.swap(temp);
		return move(temp);
	}
	
	void execute(const vector<executable_statement>& statements)
	{
		execute(statements, execute_one);
	}
	
	void execute_one([[gnu::nonnull]] state* __restrict__ state, executable_statement statement) noexcept
	{
#define OP_CASE(n)	case opcode::n: n(state, statement); break
		switch (statement.opcode)
		{
			OP_CASE(dec_ptr);
			OP_CASE(dec_value);
			OP_CASE(inc_ptr);
			OP_CASE(inc_value);
			OP_CASE(input);
			OP_CASE(output);
			OP_CASE(loop_enter);
			OP_CASE(loop_exit);
			default: break;
		}
	}
}

extern "C" void go_to([[gnu::nonnull]] brainfuck::state* __restrict__ state, unsigned dest) noexcept
{
	state->ip = dest;
}
