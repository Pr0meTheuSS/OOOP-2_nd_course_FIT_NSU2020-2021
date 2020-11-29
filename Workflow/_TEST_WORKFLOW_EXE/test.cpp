#include "pch.h"
#include <iostream>
#include "../Block.h"
#include "../Executor.h"
#include "../WorkFlow.h"



// “есты дл€ проверки работоспособности каждого блока-обработчика по отдельности
 TEST(Block_exe, ReadFiletest_file_no_exist) {
	 std::vector<std::string> args;
	 std::string filename = "this_file_doesnot_exist.txt";
	 args.push_back(filename);  
	 try {
		 Readfile RF(args);
	 }
	 catch (const char* e) {
		 ASSERT_EQ(e, "\nCannot open this file\n");
	 }
 }

 TEST(Block_exe, ReadFiletest_simple_file) {
	 std::vector<std::string> args;
	 std::string filename = "test.txt";
	 args.push_back(filename);
	 Readfile RF(args);
	 std::vector <std::string> data;
	 data = RF.process_request(data);	
 }
 
 TEST(Block_exe, WriteFiletest) {
	 std::vector<std::string> args_for_request;
	 char* strings[] = { "Some_string\n" ,
		 "Someloooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong_string",
			" str33ng_w1th_n4mb3r\n", " ", "\n", "", "CAPS_LOCK\n", "\|/?!&*^%$#@)(<_+=->\n" };//8 строк
	 for(int i = 0; i < 8; i++)
	 args_for_request.push_back(strings[i]);
	 std::string filename = "output_test_writefile.txt";
	 std::vector <std::string> arg_for_constructor;
	 arg_for_constructor.push_back(filename);
	 Writefile WF(arg_for_constructor);
	 std::vector < std::string> request_answer = WF.process_request(args_for_request);
	EXPECT_TRUE(request_answer.empty());
 }

 TEST(Block_exe, Replacetest) {

	 
	 std::vector<std::string> args;

	 std::string word_1 = "world";
	 std::string word_2 = "friend";
	 args.push_back(word_1);
	 args.push_back(word_2);

	 Replace Rpl(args);

	 std::string text = "What a wounderful world! Hello world!";
	 std::vector<std::string> data;
	 data.push_back(text);
	 data = Rpl.process_request(data);

	 EXPECT_EQ("What a wounderful friend! Hello friend!", data[0]);
 }

 TEST(Block_exe, Greptest) {

	 std::string to_grep = "friend";

	 std::string str_arr[] = { "Do you want to have a friend \n",  "and freind ly  boy\n ", "sBand friend \n" };
	 std::vector<std::string> data;
	 for (int i = 0; i < 3; i++)
		 data.push_back(str_arr[i]);

	 std::vector<std::string> args;
	 args.push_back(to_grep);
	 
	 Grep  Grp(args);

	 data = Grp.process_request(data);

	 EXPECT_EQ(data.size(), (size_t)2);

	 EXPECT_EQ(str_arr[0], data[0]);
	 EXPECT_EQ(str_arr[2], data[1]);

 }

 TEST(Block_exe, Sorttest) {
	 std::string strings[] = { "blog",  "algol", "algorithm", "war", "arithmetic", "blag"};
	 std::string number_str[] = {"100", "250", "-800", "12.5", "-185.05"};
	 
	 std::vector<std::string> data;
	 
	 for(int i = 0; i < 6; i++)
		data.push_back(strings[i]);
	 
	 Sort S;
	 data = S.process_request(data);

	 EXPECT_EQ(data.size(), 6);// data.size() == len(strings)

	 EXPECT_EQ(data[0], strings[1]);//algol
	 EXPECT_EQ(data[1], strings[2]);//algorithm
	 EXPECT_EQ(data[2], strings[4]);//arithmetic
	 EXPECT_EQ(data[3], strings[5]);//blag
	 EXPECT_EQ(data[4], strings[0]);//blog
	 EXPECT_EQ(data[5], strings[3]);//war

 }



 TEST(Block_exe, Dumptest) {

	 std::vector<std::string> args_for_request;

	 std::string strings[] = { "Some_string\n" ,
		 "Someloooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong_string",
			" str33ng_w1th_n4mb3r\n", " ", "\n", "", "CAPS_LOCK\n", "\|/?!&*^%$#@)(<_+=->\n" };//8 строк
	 
	 for (size_t i = 0; i < 8; i++)
		 args_for_request.push_back(strings[i]);
	 
	 std::string filename = "output_test_dump.txt";
	 std::vector <std::string> arg_for_constructor;
	 arg_for_constructor.push_back(filename);
	 
	 Dump DF(arg_for_constructor);
	 
	 std::vector <std::string> request_answer = DF.process_request(args_for_request);
	 
	 EXPECT_EQ(request_answer.size(), 8);

	 for(size_t i = 0; i < 8; i++)
		 EXPECT_EQ(strings[i], request_answer[i]);
 }


 //ѕроверка работоспособности св€зной работы блоков-обработчиков на валидных последовательност€х команд 


 TEST(Executor_chain, ExePnormal_test_data) {
	//отладить - при дампе (перед дампом ) происходит сли€ние всех строк (исчезают все разделители) - так не должно быть  
	 Executor exe;
	 
	 std::vector<std::string> commands =					 {"readfile" , "sort" ,      "replace",            "dump" ,       "grep" ,   "writefile"};
	 std::vector<std::vector<std::string>> array_of_args = { {"input.txt"}, {},   {"worrior", "lawer"}, {"dump_file.txt"}, {"bread"},  {"output.txt"} };
	 std::vector<size_t> id_s =									{0,			  2,			1,					 3,				4,				5 };
	 
	 for(size_t i = 0; i < commands.size(); i++)
		 exe.add_block(id_s[i], commands[i], array_of_args[i]);
	 exe.process_requests(id_s);
 }


 //TEST(Workflow, Wrong_data_in_workflow_file) {
	//
	// try {
	//	 WorkFlow WF_1("Workflow_wrong_1.txt");
	// }
	// catch (const char* e) { EXPECT_EQ(0, strcmp(e, "\nError: Invalid synthax in workflow file, escape keywords \"desc\", \"csed\"\n") ); }
	// try {
	//	 WorkFlow WF_2("Workflow_wrong_2.txt");
	// }
	// catch (const char* e) { EXPECT_EQ(e, "\nError on class Executor: block id does not exist\n"); }

	// try {
	//	 WorkFlow WF_3("Workflow_wrong_3.txt");
	// }
	// catch (const char* e) { EXPECT_EQ(e, "\nIn class Replace: vector args's size is not right\n"); }

	// try {
	//	 WorkFlow WF_4("Workflow_wrong_4.txt");
	// }
	// catch (const char* e) { EXPECT_EQ(e, "\nException in class Executor: Unknown command in constructor\n"); }

	// try {
	//	 WorkFlow WF_5("Workflow_wrong_5.txt");
	// }
	// catch (const char* e) { EXPECT_EQ(e, "\nError: class Executor: command id is not unique\n"); }

 //}



