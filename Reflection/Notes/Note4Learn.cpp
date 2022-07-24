UE 的反射

1，注册阶段

基于 UHT ， UBT 生成反射信息和代码

UCLASS() ， UPROPERTY() ， UFUNCTION() ， 都是空的宏，用来标记在引擎和项目中需要生成反射信息的代码， UHT 会根据这些标记来生成对应的反射信息

反射信息一般生成在 xxx.generated.h 和 xxx.gen.cpp 文件中，参与引擎和项目的编译

GENERATED_BODY() ， 生成的反射代码通过宏引入到引擎和项目中

#define BODY_MACRO_COMBINE_INNER(A,B,C,D) A##B##C##D
#define BODY_MACRO_COMBINE(A,B,C,D) BODY_MACRO_COMBINE_INNER(A,B,C,D)
#define GENERATED_BODY(...) BODY_MACRO_COMBINE(CURRENT_FILE_ID,_,__LINE__,_GENERATED_BODY);
可见 GENERATED_BODY() 展开其实就是生成了另一个宏
举个例子，FID_Reflection_Plugins_ReflectionPlugin_Source_ReflectionPlugin_Public_TestActor_h_13_GENERATED_BODY
4个参数分别是：
    1，参数1 CURRENT_FILE_ID 对应 FID_Reflection_Plugins_ReflectionPlugin_Source_ReflectionPlugin_Public_TestActor_h 实际就是 TestActor.h 对于项目根目录的相对路径
    2，参数2固定是 "_"
    3，参数3 __LINE__ 对应 TestActor.h 文件下使用 GENERATED_BODY 宏的行号
    4，参数4固定是 "GENERATED_BODY"

举个例子，展开 FID_Reflection_Plugins_ReflectionPlugin_Source_ReflectionPlugin_Public_TestActor_h_13_GENERATED_BODY 宏
{
    public:
        FID_Reflection_Plugins_ReflectionPlugin_Source_ReflectionPlugin_Public_TestActor_h_13_SPARSE_DATA
        FID_Reflection_Plugins_ReflectionPlugin_Source_ReflectionPlugin_Public_TestActor_h_13_RPC_WRAPPERS_NO_PURE_DECLS
        FID_Reflection_Plugins_ReflectionPlugin_Source_ReflectionPlugin_Public_TestActor_h_13_CALLBACK_WRAPPERS
        FID_Reflection_Plugins_ReflectionPlugin_Source_ReflectionPlugin_Public_TestActor_h_13_INCLASS_NO_PURE_DECLS
        FID_Reflection_Plugins_ReflectionPlugin_Source_ReflectionPlugin_Public_TestActor_h_13_ENHANCED_CONSTRUCTORS
    private:
}
如上面代码块，展开后又是另外的一些宏 =_=
下面一个个分析分别干了些什么东东

举个例子，展开 FID_Reflection_Plugins_ReflectionPlugin_Source_ReflectionPlugin_Public_TestActor_h_13_SPARSE_DATA 宏
目前只看到是个空宏，不知道用来干嘛      @TODO

举个例子，展开 FID_Reflection_Plugins_ReflectionPlugin_Source_ReflectionPlugin_Public_TestActor_h_13_RPC_WRAPPERS_NO_PURE_DECLS 宏
{
    virtual int32 TestUFuncBpNative_Implementation(const FString& InStr);
	DECLARE_FUNCTION(execTestUFuncBpNative);
	DECLARE_FUNCTION(execTestUFuncBpCallable);
	DECLARE_FUNCTION(execTestUFuncOnly);
}

举个例子，展开 FID_Reflection_Plugins_ReflectionPlugin_Source_ReflectionPlugin_Public_TestActor_h_13_CALLBACK_WRAPPERS 宏
目前只看到是个空宏，不知道用来干嘛      @TODO

举个例子，展开 FID_Reflection_Plugins_ReflectionPlugin_Source_ReflectionPlugin_Public_TestActor_h_13_INCLASS_NO_PURE_DECLS 宏
{
    private:
        static void StaticRegisterNativesATestActor();
        friend struct Z_Construct_UClass_ATestActor_Statics;
    public: \
        DECLARE_CLASS(ATestActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ReflectionPlugin"), NO_API)
        DECLARE_SERIALIZER(ATestActor)
}

举个例子，展开 FID_Reflection_Plugins_ReflectionPlugin_Source_ReflectionPlugin_Public_TestActor_h_13_ENHANCED_CONSTRUCTORS 宏
{
    private:
        /** Private move- and copy-constructors, should never be used */
        NO_API ATestActor(ATestActor&&);
        NO_API ATestActor(const ATestActor&);
    public:
        DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATestActor);
        DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATestActor);
        DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATestActor)
}

解析 DECLARE_FUNCTION
//
// Blueprint VM intrinsic return value declaration.
//
#define RESULT_PARAM Z_Param__Result
#define RESULT_DECL void*const RESULT_PARAM
// This macro is used to declare a thunk function in autogenerated boilerplate code
#define DECLARE_FUNCTION(func) static void func( UObject* Context, FFrame& Stack, RESULT_DECL )
举个例子，展开 DECLARE_FUNCTION(execTestUFuncBpCallable);
{
    static void execTestUFuncBpCallable( UObject* Context, FFrame& Stack, void*const Z_Param__Result )
}
其实就是在 ATestActor 类里声明了个静态方法，参数是 UObject* ， FFrame& ， void*const 。

解析 DEFINE_FUNCTION
// This macro is used to define a thunk function in autogenerated boilerplate code
#define DEFINE_FUNCTION(func) void func( UObject* Context, FFrame& Stack, RESULT_DECL )
举个例子，展开 DEFINE_FUNCTION(ATestActor::execTestUFuncBpCallable)
{
    void ATestActor::execTestUFuncBpCallable( UObject* Context, FFrame& Stack, void*const Z_Param__Result )
    {
        P_GET_PROPERTY(FStrProperty,Z_Param_InStr);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->TestUFuncBpCallable(Z_Param_InStr);
		P_NATIVE_END;
    }
}
其实就是定义上面用 DECLARE_FUNCTION 声明过的静态方法。
结合 DECLARE_FUNCTION 和 DEFINE_FUNCTION 2个来看，其实主要就是生成个 thunk 方法。但为什么要生成个 thunk 方法呢，首先看方法的逻辑是给蓝图VM调用的，就是我们cpp的接口 TestUFuncBpCallable 通过 execTestUFuncBpCallable 来调，另一方面，如果单从要实现反射层面来思考，我们cpp接口 TestUFuncBpCallable 要注册，但又不是直接注册 TestUFuncBpCallable ，而是套多一层 execTestUFuncBpCallable 静态方法。所以目前个人认为，生成个 thunk 方法，套多一层巧妙同时解决了2个问题。






