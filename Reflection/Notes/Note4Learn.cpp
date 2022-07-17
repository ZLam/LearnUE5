UE 的反射

基于 UHT ， UBT 生成反射信息和代码

UCLASS() ， UPROPERTY() ， UFUNCTION() ， 都是空的宏，用来标记在引擎和项目中需要生成反射信息的代码， UHT 会根据这些标记来生成对应的反射信息

反射信息一般生成在 xxx.generated.h 和 xxx.gen.cpp 文件中，参与引擎和项目的编译

GENERATED_BODY() ， 生成的反射代码通过宏引入到引擎和项目中

#define BODY_MACRO_COMBINE_INNER(A,B,C,D) A##B##C##D
#define BODY_MACRO_COMBINE(A,B,C,D) BODY_MACRO_COMBINE_INNER(A,B,C,D)
#define GENERATED_BODY(...) BODY_MACRO_COMBINE(CURRENT_FILE_ID,_,__LINE__,_GENERATED_BODY);
可见 GENERATED_BODY() 展开其实就是生成了另一个宏，例如 FID_Reflection_Plugins_ReflectionPlugin_Source_ReflectionPlugin_Public_TestActor_h_13_GENERATED_BODY
4个参数分别是：
1，参数1对应 FID_Reflection_Plugins_ReflectionPlugin_Source_ReflectionPlugin_Public_TestActor_h 实际就是 TestActor.h 




