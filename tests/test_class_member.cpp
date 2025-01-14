#include "lua_tinker.h"
#include"test.h"
extern std::map<std::string, std::function<bool()> > g_test_func_set;

void test_class_member(lua_State* L)
{

	g_test_func_set["test_lua_member_property"] = [L]()->bool
	{
	    //raw string R"()" 不會進行轉義
		std::string luabuf =
			R"(function test_lua_member_property()
					local pFFShared =  make_ff();
					local raw_pff = pFFShared:_get_raw_ptr();
					raw_pff.m_prop = 88;
					return raw_pff.m_prop == 88;
				end	
			)";
		lua_tinker::dostring(L, luabuf.c_str());// 执行lua脚本，如果是文件则需要调用lua::dofile。
		return  lua_tinker::call<bool>(L, "test_lua_member_property");//调用lua中的函数 函數名：test_lua_member_property , 參數名稱省略
	};
	g_test_func_set["test_lua_member_readonly_1"] = [L]()->bool
	{
		std::string luabuf =
			R"(function test_lua_member_readonly_1()
					local pFF1 = ff(1);
					return pFF1.m_prop_readonly;
				end
			)";
		lua_tinker::dostring(L, luabuf.c_str());
		return 1 == lua_tinker::call<int>(L, "test_lua_member_readonly_1");
	};
	g_test_func_set["test_lua_member_readonly_2"] = [L]()->bool
	{
		std::string luabuf =
			R"(function test_lua_member_readonly_2()
					local pFF1 = ff(1);
					pFF1.m_prop_readonly = 88; --error readonly
				end
			)";
		lua_tinker::dostring(L, luabuf.c_str());
		lua_tinker::set_error_callback([](lua_State *L) -> int
		{
			std::string errinfo(lua_tostring(L, -1));
			if (errinfo != "property didn't have set_func")
			{
				lua_tinker::on_error(L);
			}
			return 0;
		});
		lua_tinker::call<void>(L, "test_lua_member_readonly_2");
		lua_tinker::set_error_callback(&lua_tinker::on_error);

		return true;

	};

	g_test_func_set["test_lua_member_static"] = [L]()->bool
	{
		std::string luabuf =
			R"(function test_lua_member_static()
					local pFF1 = ff(1);
					pFF1.s_val = 901;
					local pFF2 = ff(2);
					return pFF2.s_val == 901;
				end
			)";
		lua_tinker::dostring(L, luabuf.c_str());
		return lua_tinker::call<bool>(L, "test_lua_member_static");
	};
	g_test_func_set["test_lua_var_static"] = [L]()->bool
	{
		std::string luabuf =
			R"(function test_lua_var_static()
					return ff.ENUM_1;
				end
			)";
		lua_tinker::dostring(L, luabuf.c_str());
		return ff::ENUM_1 == lua_tinker::call<int>(L, "test_lua_var_static");
	};




}