// file autogenerated by interpiler
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <unordered_map>
#include <string>
#include <vector>

class ir_generator
{
	llvm::LLVMContext& context;
	llvm::Module& module;

public:
	llvm::Function* function;
	llvm::BasicBlock* lastBlock;

private:
	std::unordered_map<std::string, llvm::Type*> struct_types;
	std::vector<llvm::Type*> types;
	std::vector<llvm::GlobalValue*> globals;

public:
	llvm::IRBuilder<> builder;

public:
	ir_generator(llvm::LLVMContext& context, llvm::Module& module);

private:
	void make_types();
	void make_globals();

public:
	void start_function(llvm::FunctionType& type, const std::string& name);
	llvm::Function* end_function();
	llvm::BasicBlock* start_block(const std::string& name = "");
	llvm::Type* type_by_name(const std::string& name);
	void dec_ptr(llvm::Value* arg0, llvm::Value* arg1);
	void dec_value(llvm::Value* arg0, llvm::Value* arg1);
	void inc_ptr(llvm::Value* arg0, llvm::Value* arg1);
	void inc_value(llvm::Value* arg0, llvm::Value* arg1);
	void input(llvm::Value* arg0, llvm::Value* arg1);
	void output(llvm::Value* arg0, llvm::Value* arg1);
	void loop_enter(llvm::Value* arg0, llvm::Value* arg1);
	void loop_exit(llvm::Value* arg0, llvm::Value* arg1);
};
