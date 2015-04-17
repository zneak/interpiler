// file autogenerated by interpiler
#include <llvm/IR/Constants.h>
#include "irgen.h"

ir_generator::ir_generator(llvm::LLVMContext& context, llvm::Module& module)
	: context(context), module(module), function(nullptr), lastBlock(nullptr), builder(context)
{
	make_types();
	make_globals();
}

void ir_generator::make_types()
{
	types.resize(10);
	using namespace llvm;
	types[0] = IntegerType::get(context, 64);
	types[1] = IntegerType::get(context, 32);
	types[2] = IntegerType::get(context, 8);
	ArrayRef<Type*> func_type_params_3 = { };
	types[3] = FunctionType::get(types[1], func_type_params_3, false);
	ArrayRef<Type*> func_type_params_4 = { types[1], };
	types[4] = FunctionType::get(types[1], func_type_params_4, false);
	StructType* struct_5 = StructType::create(context, "struct.brainfuck::state");
	types[5] = struct_5;
	struct_types["struct.brainfuck::state"] = struct_5;
	types[6] = ArrayType::get(types[2], 4096);
	ArrayRef<Type*> struct_type_params_5 = { types[6], types[0], types[1], };
	struct_5->setBody(struct_type_params_5, false);
	types[7] = PointerType::get(types[5], 0);
	ArrayRef<Type*> func_type_params_8 = { types[7], types[1], };
	types[8] = Type::getVoidTy(context);
	types[9] = FunctionType::get(types[8], func_type_params_8, false);
}

void ir_generator::make_globals()
{
	globals.resize(3);
	using namespace llvm;
	globals[0] = llvm::Function::Create(cast<FunctionType>(types[3]), llvm::GlobalValue::ExternalLinkage, "getchar", &module);
	globals[1] = llvm::Function::Create(cast<FunctionType>(types[4]), llvm::GlobalValue::ExternalLinkage, "putchar", &module);
	globals[2] = llvm::Function::Create(cast<FunctionType>(types[9]), llvm::GlobalValue::ExternalLinkage, "go_to", &module);
}

void ir_generator::start_function(llvm::FunctionType& type, const std::string& name)
{
	assert(function == nullptr && "unterminated function");
	assert(type.getReturnType()->isVoidTy() && "created functions must return void");
	function = llvm::Function::Create(&type, llvm::GlobalValue::ExternalLinkage, name, &module);
	start_block();
}

llvm::Function* ir_generator::end_function()
{
	builder.CreateRetVoid();
	auto fn = function;
	function = nullptr;
	return fn;
}

llvm::BasicBlock* ir_generator::start_block(const std::string& name)
{
	lastBlock = llvm::BasicBlock::Create(context, name, function);
	if (builder.GetInsertBlock() != nullptr)
	{
		builder.CreateBr(lastBlock);
	}
	builder.SetInsertPoint(lastBlock);
	return lastBlock;
}

llvm::Type* ir_generator::type_by_name(const std::string& name)
{
	auto iter = struct_types.find(name);
	assert(iter != struct_types.end());
	return iter->second;
}

void ir_generator::dec_ptr(llvm::Value* arg0, llvm::Value* arg1)
{
	using namespace llvm;
	Constant* gep2_val2_int = ConstantInt::get(types[0], 0);
	Constant* gep2_val3_int = ConstantInt::get(types[1], 1);
	ArrayRef<Value*> gep2_array { gep2_val2_int, gep2_val3_int, };
	Value* gep2_var = builder.CreateInBoundsGEP(arg0, gep2_array);
	llvm::LoadInst* load5_var = builder.CreateLoad(gep2_var, false);
	load5_var->setAlignment(8);
	Constant* binop6_val6_int = ConstantInt::get(types[0], 4095);
	Value* binop6_var = BinaryOperator::Create(Instruction::Add, load5_var, binop6_val6_int, "", builder.GetInsertBlock());
	Value* binop8_var = BinaryOperator::Create(Instruction::And, binop6_var, binop6_val6_int, "", builder.GetInsertBlock());
	llvm::StoreInst* store9_var = builder.CreateStore(binop8_var, gep2_var, false);
	store9_var->setAlignment(8);
	lastBlock = builder.GetInsertBlock();
	return;
}

void ir_generator::dec_value(llvm::Value* arg0, llvm::Value* arg1)
{
	using namespace llvm;
	Constant* gep2_val2_int = ConstantInt::get(types[0], 0);
	Constant* gep2_val3_int = ConstantInt::get(types[1], 1);
	ArrayRef<Value*> gep2_array { gep2_val2_int, gep2_val3_int, };
	Value* gep2_var = builder.CreateInBoundsGEP(arg0, gep2_array);
	llvm::LoadInst* load5_var = builder.CreateLoad(gep2_var, false);
	load5_var->setAlignment(8);
	Constant* gep6_val6_int = ConstantInt::get(types[1], 0);
	ArrayRef<Value*> gep6_array { gep2_val2_int, gep6_val6_int, load5_var, };
	Value* gep6_var = builder.CreateInBoundsGEP(arg0, gep6_array);
	llvm::LoadInst* load8_var = builder.CreateLoad(gep6_var, false);
	load8_var->setAlignment(1);
	Constant* binop9_val9_int = ConstantInt::get(types[2], 255);
	Value* binop9_var = BinaryOperator::Create(Instruction::Add, load8_var, binop9_val9_int, "", builder.GetInsertBlock());
	llvm::StoreInst* store11_var = builder.CreateStore(binop9_var, gep6_var, false);
	store11_var->setAlignment(1);
	lastBlock = builder.GetInsertBlock();
	return;
}

void ir_generator::inc_ptr(llvm::Value* arg0, llvm::Value* arg1)
{
	using namespace llvm;
	Constant* gep2_val2_int = ConstantInt::get(types[0], 0);
	Constant* gep2_val3_int = ConstantInt::get(types[1], 1);
	ArrayRef<Value*> gep2_array { gep2_val2_int, gep2_val3_int, };
	Value* gep2_var = builder.CreateInBoundsGEP(arg0, gep2_array);
	llvm::LoadInst* load5_var = builder.CreateLoad(gep2_var, false);
	load5_var->setAlignment(8);
	Constant* binop6_val6_int = ConstantInt::get(types[0], 1);
	Value* binop6_var = BinaryOperator::Create(Instruction::Add, load5_var, binop6_val6_int, "", builder.GetInsertBlock());
	Constant* binop8_val8_int = ConstantInt::get(types[0], 4095);
	Value* binop8_var = BinaryOperator::Create(Instruction::And, binop6_var, binop8_val8_int, "", builder.GetInsertBlock());
	llvm::StoreInst* store10_var = builder.CreateStore(binop8_var, gep2_var, false);
	store10_var->setAlignment(8);
	lastBlock = builder.GetInsertBlock();
	return;
}

void ir_generator::inc_value(llvm::Value* arg0, llvm::Value* arg1)
{
	using namespace llvm;
	Constant* gep2_val2_int = ConstantInt::get(types[0], 0);
	Constant* gep2_val3_int = ConstantInt::get(types[1], 1);
	ArrayRef<Value*> gep2_array { gep2_val2_int, gep2_val3_int, };
	Value* gep2_var = builder.CreateInBoundsGEP(arg0, gep2_array);
	llvm::LoadInst* load5_var = builder.CreateLoad(gep2_var, false);
	load5_var->setAlignment(8);
	Constant* gep6_val6_int = ConstantInt::get(types[1], 0);
	ArrayRef<Value*> gep6_array { gep2_val2_int, gep6_val6_int, load5_var, };
	Value* gep6_var = builder.CreateInBoundsGEP(arg0, gep6_array);
	llvm::LoadInst* load8_var = builder.CreateLoad(gep6_var, false);
	load8_var->setAlignment(1);
	Constant* binop9_val9_int = ConstantInt::get(types[2], 1);
	Value* binop9_var = BinaryOperator::Create(Instruction::Add, load8_var, binop9_val9_int, "", builder.GetInsertBlock());
	llvm::StoreInst* store11_var = builder.CreateStore(binop9_var, gep6_var, false);
	store11_var->setAlignment(1);
	lastBlock = builder.GetInsertBlock();
	return;
}

void ir_generator::input(llvm::Value* arg0, llvm::Value* arg1)
{
	using namespace llvm;
	CallInst* call2_var = builder.CreateCall(globals[0]);
	call2_var->setTailCall();
	call2_var->setDoesNotThrow();
	Value* cast4_var = builder.CreateCast(Instruction::Trunc, call2_var, types[2]);
	Constant* gep5_val5_int = ConstantInt::get(types[0], 0);
	Constant* gep5_val6_int = ConstantInt::get(types[1], 1);
	ArrayRef<Value*> gep5_array { gep5_val5_int, gep5_val6_int, };
	Value* gep5_var = builder.CreateInBoundsGEP(arg0, gep5_array);
	llvm::LoadInst* load8_var = builder.CreateLoad(gep5_var, false);
	load8_var->setAlignment(8);
	Constant* gep9_val9_int = ConstantInt::get(types[1], 0);
	ArrayRef<Value*> gep9_array { gep5_val5_int, gep9_val9_int, load8_var, };
	Value* gep9_var = builder.CreateInBoundsGEP(arg0, gep9_array);
	llvm::StoreInst* store11_var = builder.CreateStore(cast4_var, gep9_var, false);
	store11_var->setAlignment(1);
	lastBlock = builder.GetInsertBlock();
	return;
}

void ir_generator::output(llvm::Value* arg0, llvm::Value* arg1)
{
	using namespace llvm;
	Constant* gep2_val2_int = ConstantInt::get(types[0], 0);
	Constant* gep2_val3_int = ConstantInt::get(types[1], 1);
	ArrayRef<Value*> gep2_array { gep2_val2_int, gep2_val3_int, };
	Value* gep2_var = builder.CreateInBoundsGEP(arg0, gep2_array);
	llvm::LoadInst* load5_var = builder.CreateLoad(gep2_var, false);
	load5_var->setAlignment(8);
	Constant* gep6_val6_int = ConstantInt::get(types[1], 0);
	ArrayRef<Value*> gep6_array { gep2_val2_int, gep6_val6_int, load5_var, };
	Value* gep6_var = builder.CreateInBoundsGEP(arg0, gep6_array);
	llvm::LoadInst* load8_var = builder.CreateLoad(gep6_var, false);
	load8_var->setAlignment(1);
	Value* cast9_var = builder.CreateCast(Instruction::ZExt, load8_var, types[1]);
	CallInst* call10_var = builder.CreateCall(globals[1], cast9_var);
	call10_var->setTailCall();
	call10_var->setDoesNotThrow();
	lastBlock = builder.GetInsertBlock();
	return;
}

void ir_generator::loop_enter(llvm::Value* arg0, llvm::Value* arg1)
{
	using namespace llvm;
	BasicBlock* block1 = BasicBlock::Create(context, "", function);
	BasicBlock* block2 = BasicBlock::Create(context, "", function);
	Constant* gep2_val2_int = ConstantInt::get(types[0], 0);
	Constant* gep2_val3_int = ConstantInt::get(types[1], 1);
	ArrayRef<Value*> gep2_array { gep2_val2_int, gep2_val3_int, };
	Value* gep2_var = builder.CreateInBoundsGEP(arg0, gep2_array);
	llvm::LoadInst* load5_var = builder.CreateLoad(gep2_var, false);
	load5_var->setAlignment(8);
	Constant* gep6_val6_int = ConstantInt::get(types[1], 0);
	ArrayRef<Value*> gep6_array { gep2_val2_int, gep6_val6_int, load5_var, };
	Value* gep6_var = builder.CreateInBoundsGEP(arg0, gep6_array);
	llvm::LoadInst* load8_var = builder.CreateLoad(gep6_var, false);
	load8_var->setAlignment(1);
	Constant* cmp9_val9_int = ConstantInt::get(types[2], 0);
	Value* cmp9_var = builder.CreateICmp(CmpInst::ICMP_EQ, load8_var, cmp9_val9_int);
	builder.CreateCondBr(cmp9_var, block1, block2);
	
	builder.SetInsertPoint(block1);
	Value* cast11_var = builder.CreateCast(Instruction::Trunc, arg1, types[1]);
	CallInst* call12_var = builder.CreateCall2(globals[2], arg0, cast11_var);
	call12_var->setTailCall();
	call12_var->setDoesNotReturn();
	call12_var->setDoesNotThrow();
	builder.CreateUnreachable();
	
	builder.SetInsertPoint(block2);
	lastBlock = builder.GetInsertBlock();
	return;
}

void ir_generator::loop_exit(llvm::Value* arg0, llvm::Value* arg1)
{
	using namespace llvm;
	BasicBlock* block1 = BasicBlock::Create(context, "", function);
	BasicBlock* block2 = BasicBlock::Create(context, "", function);
	Constant* gep2_val2_int = ConstantInt::get(types[0], 0);
	Constant* gep2_val3_int = ConstantInt::get(types[1], 1);
	ArrayRef<Value*> gep2_array { gep2_val2_int, gep2_val3_int, };
	Value* gep2_var = builder.CreateInBoundsGEP(arg0, gep2_array);
	llvm::LoadInst* load5_var = builder.CreateLoad(gep2_var, false);
	load5_var->setAlignment(8);
	Constant* gep6_val6_int = ConstantInt::get(types[1], 0);
	ArrayRef<Value*> gep6_array { gep2_val2_int, gep6_val6_int, load5_var, };
	Value* gep6_var = builder.CreateInBoundsGEP(arg0, gep6_array);
	llvm::LoadInst* load8_var = builder.CreateLoad(gep6_var, false);
	load8_var->setAlignment(1);
	Constant* cmp9_val9_int = ConstantInt::get(types[2], 0);
	Value* cmp9_var = builder.CreateICmp(CmpInst::ICMP_EQ, load8_var, cmp9_val9_int);
	builder.CreateCondBr(cmp9_var, block2, block1);
	
	builder.SetInsertPoint(block1);
	Value* cast11_var = builder.CreateCast(Instruction::Trunc, arg1, types[1]);
	CallInst* call12_var = builder.CreateCall2(globals[2], arg0, cast11_var);
	call12_var->setTailCall();
	call12_var->setDoesNotReturn();
	call12_var->setDoesNotThrow();
	builder.CreateUnreachable();
	
	builder.SetInsertPoint(block2);
	lastBlock = builder.GetInsertBlock();
	return;
}

