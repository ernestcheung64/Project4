#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <vector>
#include "GLFW/glfw3.h"

using std::cout;
using std::endl;
using std::string;

#if 0
class Log
{
private:
	int m_LogLevel = LogLevelInfo;
public:
	const int LogLevelError = 0;
	const int LogLevelWarning = 1;
	const int LogLevelInfo = 2;

	void SetLevel(int level)
	{
		m_LogLevel = level;
	}
	
	void Warn(const char* message)
	{
		std::cout << "[WARNING]:" << message << std::endl;
	}
	void Error(const char* message)
	{
		std::cout << "[ERROR]:" << message << std::endl;
	}
	void Info(const char* message)
	{
		std::cout << "[INFO]:" << message << std::endl;
	}
};

int main()
{
	Log log;
	log.SetLevel(log.LogLevelWarning);
	log.Warn("Hello");
	log.Error("Hello");
	log.Info("Hello");
	return 0;
}
#endif

#if 0
extern int s_Variable = 10;
//s_Variable = 20;//invalid



int main()
{
	std::cout << s_Variable << std::endl;
	return 0;
}
#endif


#if 0
struct Entity
{
	static int x, y;
	void Print()
	{
		std::cout << x << "," << y << std::endl;
	}//static methods cannot access non-static members of the class, because static members are shared by all instances of the class, they are not unique to each instance.
};

static void Print(Entity e)//this is valid because this static method is not a member of the class, it is a free function that takes an Entity as a parameter. It can access the static members of the class because they are shared by all instances of the class, but it cannot access non-static members of the class because they are unique to each instance of the class.
{
	std::cout << e.x << "," << e.y << std::endl;
}

int Entity::x = 2;
int Entity::y = 3;

int main()
{
	//Entity e{ 2,3 };//this will not work because x and y are static, they are shared by all instances of the class, they are not unique to each instance. So we cannot initialize them in the constructor, we have to initialize them outside the class definition.
	Entity e;
	Entity e1;
	e.x = 4;//this will change the value of x for all instances of the class, because x is static, it is shared by all instances of the class.
	e.y = 5;//this will change the value of y for all instances of the class, because y is static, it is shared by all instances of the class.
	e1.x = 6;
	e1.y = 7;
	e.Print();
	e1.Print();
	return 0;
}
#endif

#if 0
class Singleton
{
private:
	static Singleton* s_Instance;
public:
	static Singleton& Get() { return *s_Instance; }
	void Hello() {}
};

Singleton* Singleton::s_Instance = new Singleton();
//这一条语句必不可少，因为它定义了静态成员变量s_Instance，并且初始化了它为一个新的Singleton对象。

void funciton()
{
	//int i = 0;
	static int i = 0;
	i++;//the change of i will be preserved across function calls, because it is static, it is shared by all instances of the function, it is not unique to each instance of the function. So when we call the function multiple times, the value of i will be incremented each time, and it will be preserved across function calls.
	std::cout << i << std::endl;
}
int main()
{
	funciton();
	funciton();
	funciton();//递归？
	
	Singleton::Get().Hello();//1.Evaluate Singleton::Get() → returns Singleton& (here implemented as *s_Instance). 2.Use the dot operator on that reference to call Hello().
	//非常fancy的一条语句
	return 0;
} 
#endif

#if 0
class Singleton
{
public:
	static Singleton& Get() 
	{ 
		static Singleton Instance;
		//因为函数的返回类型是Singleton&，所以这里定义了一个静态的Singleton对象Instance，并且返回它的引用。这个Instance对象只会被创建一次，并且在程序的整个生命周期内都存在，所以它是一个单例对象。每次调用Get()函数时，都会返回同一个Instance对象的引用。 
		//这种在class内部函数的内部定义static变量的方式的好处是，Instance对象的生命周期被限制在Get()函数内部，这样就避免了静态成员变量可能带来的内存泄漏问题，因为Instance对象会在程序结束时自动销毁。
		return Instance; 
	}
	void Hello() {}
};

void funciton()
{
	//int i = 0;
	static int i = 0;
	i++;//the change of i will be preserved across function calls, because it is static, it is shared by all instances of the function, it is not unique to each instance of the function. So when we call the function multiple times, the value of i will be incremented each time, and it will be preserved across function calls.
	std::cout << i << std::endl;
}
int main()
{
	funciton();
	funciton();
	funciton();//递归？

	Singleton::Get().Hello();//1.Evaluate Singleton::Get() → returns Singleton& (here implemented as *s_Instance). 2.Use the dot operator on that reference to call Hello().
	//非常fancy的一条语句
	return 0;
}
#endif


#if 0
class Entity
{
public:
	float X, Y;
	Entity() = delete;//使外部无法调用默认构造函数创建Entity对象，必须使用带参数的构造函数来创建对象。
	Entity(float x, float y)
	{
		X = x;
		Y = y;
		std::cout << "Entity created!" << std::endl;
	}//这是一个构造函数，它在创建Entity对象时会被调用，初始化X和Y为传入的参数值。

	~Entity()
	{
		std::cout << "Entity destroyed!" << std::endl;
	}

	void Print()
	{
		std::cout << X << "," << Y << std::endl;
	}
};

void Funciton()
{
	Entity e(2.0f, 3.0f);
	e.Print();
}

int main()
{
	Funciton();
	return 0;
} 
#endif


#if 0
class Entity
{
public:
	float X, Y;

	void Move(float x, float y)
	{
		X += x;
		Y += y;
	}
};

class Player: public Entity
{
	public:
	const char* Name;
	void PrintName()
	{
		std::cout << Name << std::endl;
	}
};

int main()
{
	std::cout << sizeof(Player) << std::endl;
	//sizeof(Player) = sizeof(Entity) + sizeof(const char*) = 8 + 8 = 16 bytes. This is because Player inherits from Entity, so it has all the members of Entity (X and Y), which take up 8 bytes, and it also has its own member Name, which is a pointer to a const char, which takes up another 8 bytes. So the total size of Player is 16 bytes.
	std::cout << sizeof(Player::Name) << std::endl;
	//sizeof(Player::Name) = sizeof(const char*) = 8 bytes. This is because Name is a pointer to a const char, which takes up 8 bytes on a 64-bit system. The size of the pointer does not depend on the type it points to, so it is always 8 bytes on a 64-bit system.
	Player player;
	player.Move(5, 5);
	player.X = 10;
	player.Y = 10;
	player.Name = "John";
	//继承的好处是，Player类可以直接使用Entity类的成员变量和成员函数，而不需要重新定义它们，这样就避免了代码的重复，提高了代码的复用性和可维护性。

}
#endif

#if 0
class Entity
{
public:
	virtual std::string GetName() { return "Entity"; }
	//这是Entity类的成员函数GetName()，它返回一个字符串"Entity"，表示这个对象的类型是Entity。
	//virtual关键字表示这个函数是一个虚函数，允许在派生类中重写它，以实现多态性。当我们通过基类指针调用这个函数时，实际调用的是派生类中重写的版本，而不是基类中的版本。
};

class Player : public Entity
{
private:
	std::string m_Name;
public:
	Player(const std::string& name): m_Name(name) {
	}//这是Player类的构造函数，它接受一个const std::string&类型的参数name，并将其赋值给成员变量m_Name。这个构造函数在创建Player对象时会被调用，用于初始化m_Name成员变量。
	std::string GetName() override { return m_Name; }
};

void PrintName(Entity* entity)
{
	std::cout << entity->GetName() << std::endl;
}

int main()
{
	Entity* e = new Entity();
	//Entity后面有没有括号都可以，因为Entity类有一个默认构造函数，所以编译器会自动调用它来创建一个Entity对象。无论是Entity* e = new Entity;还是Entity* e = new Entity();都会创建一个Entity对象，并将其地址赋值给指针e。
	std::cout << e->GetName() << std::endl;
	//e->GetName() will call the GetName() function of the Entity class, because e is a pointer to an Entity object.
	Player* p = new Player("John");
	std::cout << p->GetName() << std::endl;
	PrintName(e);
	PrintName(p);
	return 0;
}
#endif

#if 0
class Entity
{
public:
	virtual std::string GetName() = 0;
	//这是Entity类的成员函数GetName()，它返回一个字符串"Entity"，表示这个对象的类型是Entity。
	//virtual关键字表示这个函数是一个虚函数，允许在派生类中重写它，以实现多态性。当我们通过基类指针调用这个函数时，实际调用的是派生类中重写的版本，而不是基类中的版本。
};

class Player : public Entity
{
private:
	std::string m_Name;
public:
	Player(const std::string& name) : m_Name(name) {
	}//这是Player类的构造函数，它接受一个const std::string&类型的参数name，并将其赋值给成员变量m_Name。这个构造函数在创建Player对象时会被调用，用于初始化m_Name成员变量。
	std::string GetName() { return m_Name; }
};

void PrintName(Entity* entity)
{
	std::cout << entity->GetName() << std::endl;
}

int main()
{
	//Entity* e = new Entity();//无法实例化一个抽象类，因为Entity类中有一个纯虚函数GetName()，它没有提供函数体，所以编译器会将Entity类视为一个抽象类，无法创建它的对象。
	Player* p = new Player("John");
	//PrintName(e);
	PrintName(p);
	return 0;
}
#endif

#if 0
class Entity
{
protected:
	int X, Y;
	void Print() {}
public://this has to be public, otherwise we cannot create an Entity object in the main function, because the constructor is private, and we cannot call it from outside the class.
	Entity()
	{
		X = 0;
		Print();
	}
};

class Player : public Entity
{
private:
	Player()
	{
		X = 5;
		Print();
	}

};

int main()
{
	Entity e;
	//e.X = 5;//invalid, because X is a private member of the Entity class, it cannot be accessed from outside the class.
	e.Print();//invalid, because Print() is a private member of the Entity class, it cannot be accessed from outside the class.
	return 0;

}
#endif

#if 0
int main()
{
	int example[5];
	std::cout << sizeof(example) << std::endl;
	//这里显示的是example的字节大小，而不是含有的元素个数。如果想要知道example的元素个数，需要除以元素类型的大小来计算，例如sizeof(example) / sizeof(int)。
	std::cout << example << std::endl;
	int* another = new int[5];
	delete[] another;
	std::array<int, 5> arr;
	std::cout << arr.size() << std::endl;
	//这里显示的是arr的元素个数，而不是字节大小。这就是std::array的好处，它可以直接获取元素个数，而不需要除以元素类型的大小来计算。
	char sentence[] = "Hello World";
	std::cout << sentence << std::endl;
	
	const char* another_sentence = "Hello World";
	//这里必须使用const char*，因为字符串字面量是不可修改的，所以必须使用指向const char的指针来存储它的地址。
	std::cout << another_sentence << std::endl;
	
	char* mutable_sentence = new char[12];
	strcpy_s(mutable_sentence, 12, "Hello World");
	//strcpy_s比strcpy更安全，因为它需要指定目标缓冲区的大小，可以防止缓冲区溢出的问题。
	cout << mutable_sentence << endl;
	delete[] mutable_sentence;
	
	return 0;
}
#endif

#if 0
void PrintString(const string& str)//采用const string&作为参数类型，可以避免不必要的字符串复制，提高性能，同时也保证了函数内部不会修改传入的字符串。
{
	std::cout << str << std::endl;
}

int main()
{
	char name[5] = { 'J','o','h','n',0};//直接写成数字0，是码值对应
	char another_name[4] = { 'J','o','h','n'};//在这里只有4个元素，没有给\0字符的空位，所以打印出来后面会有乱码
	char mutable_name[8] = { 'J','o','h','n'};
	cout << name << endl;
	cout << another_name << endl;
	cout << mutable_name << endl;

	string string_name = string("John") + ", hello!";
	bool contains = string_name.find("ohn") != string::npos;
	cout << string_name << endl;
	cout << contains << endl;

	return 0;
}
#endif

#if 0
int main()
{
    char name[8] = "John";
	const char* another_name = "Jo\0hn";
	//Because string literals have static storage and are immutable in C++; the language treats them as arrays of const char[N]. 
	// Allowing non-const access would let you try to modify memory that the implementation may place in read‑only segments.
	//在内存中这些字符都保存了，但是在打印的时候，遇到\0就会认为字符串结束了，所以只会打印出"Jo"，后面的"hn"不会被打印出来。
	name[2] = 'h';
	
	//*(another_name + 2) = 'h';
	//invalid, because another_name is a pointer to a string literal, which is stored in read-only memory.
	cout << name << endl;
	cout << another_name << endl;
	return 0;
}
#endif

#if 0
class Entity
{
private:
	int m_X, m_Y;
	mutable int var;
	
public:
	Entity()
	{
		m_X = 0;
		m_Y = 0;
		var = 0;
	}
	int GetX() const//read only method 
	{ 
		//m_X = 2;//invalid
		var = 2;
		//mutable关键字允许在const成员函数中修改这个变量的值，即使这个成员函数被声明为const，也可以修改这个变量的值。这是因为mutable变量被认为是一个例外，它不受const成员函数的限制，可以在const成员函数中被修改。
		return m_X; 
	}
};

void PrintEntity(const Entity& e)//const的作用是保证在函数内部不会修改传入的Entity对象，这样就可以安全地传递一个const Entity&类型的参数，避免了不必要的对象复制，提高了性能。
{
	//e = Entity();//invalid, because e is a reference to a const Entity object, it cannot be assigned a new value.
	//e.GetX() = 2;//invalid, because GetX() is a const member function, it cannot modify the state of the object, so it cannot be used as an lvalue to assign a new value to it.
	std::cout << e.GetX() << std::endl;
}

int main()
{
	const int  MAX_AGE = 150;
	int* a = new int;
	*a = 2;
	
	const int* another_a = new int;//一
	cout << *another_a << endl;

	int b;
	int const* another_b = new int;//二
	//*another_b = 3;

	int const* const c = new int;//三
	int* const d = new int;//四
	//d = nullptr;//invalid

	Entity e=Entity();

}
#endif

#if 0
class Entity
{
private:
	string m_Name;
	mutable int m_DebugCount = 0;
public:
	Entity(string string_name) : m_Name(string_name){}
	const string& GetName() const
	{ 
		m_DebugCount++;
		return m_Name; 
	}
	~Entity()
	{
		cout << m_Name << ":" << m_DebugCount << endl;
	}
};
int main()
{
	const Entity e("John");
	const Entity another_e = Entity("Tom");
	//两种调用构造函数的方式，第一种是直接初始化，第二种是拷贝初始化。两者的区别在于，直接初始化会直接调用构造函数来创建对象，而拷贝初始化会先创建一个临时对象，然后再调用拷贝构造函数来创建另一个对象。
	e.GetName();//the method has to be const, because e is a const Entity object
	e.GetName();
	e.GetName();
	e.GetName();
	e.GetName();
	//as long as e is still alive, m_DebugCount won't be reset to 0, it will keep increasing each time we call GetName() on e, and when e is destroyed, the destructor will print the final value of m_DebugCount, which will be 5 in this case.
	cout << e.GetName() << " first" << endl;
	auto f = [=]()//这里只是定义。这里选用=或者&的结果不一样，非常有意思
	{
		cout << e.GetName() << " second" << endl;
	};
	f();//实例化
	return 0;
}
#endif

#if 0
class Example
{
public:
	Example()
	{
		cout << "Created Entity!" << endl;
	}
	Example(int x)
	{
		cout << "Created Entity with value: " << x << endl;
	}
};

class Entity
{
private:
	string m_Name;
	int m_Score;
	Example m_Example;
public:
	Entity(const string& name)
		:m_Name(name), m_Score(0)
	{
	}
	Entity()
		:m_Name("Default Name"), m_Score(0), m_Example(8)
	{ 
		m_Example = Example(8);
		//如果没有在成员初始化列表中初始化m_Example，那么它会被默认构造函数创建一个对象，然后在构造函数体内又被赋值为一个新的对象，这样就会造成不必要的对象创建和销毁，降低性能。
	}
	const string& GetName() const 
	{ 
		return m_Name; 
	}
};

int main()
{
	//Entity e0("John");
	//cout << e0.GetName() << endl;
	Entity e1;
	cout << e1.GetName() << endl;
	return 0;
}
#endif


//三元运算符
#if 0
static int s_Level = 2;
static int s_Speed = 5;

int main()
{
	s_Speed = (s_Level > 5) ? 10 : 5;
	string rank = (s_Level > 5) ? "High" : "Low";
	return 0;
}
#endif

#if 0
class Entity
{
private:
	string m_Name;
public:
	Entity()
		:m_Name("Default Name")
	{
	}
	Entity(const string& name)
		:m_Name(name)
	{
	}
	const string& GetName() const
	{
		return m_Name;
	}
};
int main()
{
	Entity* e;
	{
		Entity entity("John");
		e = &entity;
		cout << e->GetName() << endl;
	}
	{
		Entity* entity_pr = new Entity("Tom");
		e = entity_pr;
		cout << entity_pr->GetName() << endl;
		//在运行到花括号结束时，entity_pr对象会被销毁，e指针仍然指向它的内存地址
	}
	delete e;
	return 0;
}
#endif

#if 0
class Entity
{
public:
	float X, Y;
};
int main()
{
	int a = 2;
	int* b = new int[50];
	int* c = new int;
	Entity* e = new(c)Entity[50];//有一些问题，但是能编译通过
	delete[] b;
	delete[] e;
	return 0;
}
#endif

#if 0
class Entity
{
private:
	string m_Name;
	int m_Age;
public:
	Entity(const string& name)
		:m_Name(name), m_Age(0)
	{
	}
	Entity(int age)
		:m_Name("Default Name"), m_Age(age)
	{
	}
};
void PrintEntity(const Entity& e)
{
}
int main()
{
	PrintEntity(22);
	PrintEntity((string)"John");
	Entity a("John");
	//Entity a = "John";//invalid
	Entity b(30);
	return 0;
}
#endif

#if 0
//运算符重载
struct Vector2
{
	float X, Y;

	Vector2(float x, float y)
		:X(x), Y(y)
	{
	}
	Vector2 Add(const Vector2& other) const
	{
		return Vector2(X + other.X, Y + other.Y);
	}
	Vector2 Multiply(const Vector2& other) const
	{
		return Vector2(X * other.X, Y * other.Y);
	}

	Vector2 operator+(const Vector2& other) const
	{
		return Add(other);
	}
	Vector2 operator*(const Vector2& other) const
	{
		return Multiply(other);
	}
	bool operator==(const Vector2& other) const
	{
		return X == other.X && Y == other.Y;
	}
	bool operator!=(const Vector2& other) const
	{
		return !(*this == other);
	}

};

std::ostream& operator<<(std::ostream& stream, const Vector2& other)
//这里需要返回ostream&的原因是后面需要<< endl，<<操作符前必须是ostream对象，所以需要返回ostream&来支持链式调用。
//注意这里返回void只影响和Vector2有关的特例。
{
	stream << other.X << "," << other.Y;
	return stream;
}

int main()
{
	Vector2 position(2.0f, 3.0f);
	Vector2 speed(0.5f, 1.0f);
	Vector2 powerup(1.1f, 1.1f);

	Vector2 result = position.Add(speed.Multiply(powerup));
	Vector2 result2 = position+ speed* powerup;

	cout << result2 << endl;

	return 0;
}
#endif

#if 0
class Entity;//在下一行之前要先声明class Entity
void PrintEntity(Entity& e);

class Entity
{
public:
	int x, y;
	Entity(int x, int y)
	{
		this->x = x;
		this->y = y;
		PrintEntity(*this);
	}
	int GetX() const
	{
		
		return x;
	}
};
void PrintEntity(Entity& e)
{
}
int main()
{
	Entity e(1, 1);
	return 0;
}
#endif

#if 0
class Entity
{
public:
	Entity()
	{
		cout << "Created" << endl;
	}
	~Entity()
	{
		cout << "Destroyed" << endl;
	}
};
class ScopedPtr
{
private:
	Entity* m_ptr;
public:
	ScopedPtr(Entity* e)
		:m_ptr(e)
	{
	}
	~ScopedPtr()
	{
		delete m_ptr;
	}
};
int* CreateArray()
{
	int* array = new int[50];
	return array;
}
int main()
{
	int* a = CreateArray();
	Entity* e = new Entity();
	delete e;
	ScopedPtr scopedptr = new Entity();//尽管使用new进行分配，但是通过智能指针任然可以自行控制生存域，删除指针
	return 0;
}
#endif

#if 0
//智能指针
class Entity
{
public:
	Entity()
	{
		cout << "Created" << endl;
	}
	~Entity()
	{
		cout << "Destroyed" << endl;
	}
	void Pring()
	{

	}
};
int main()
{
	std::shared_ptr<Entity> e0;
	std::weak_ptr<Entity>e00;
	{
		std::unique_ptr<Entity> e = std::make_unique<Entity>();
		std::shared_ptr<Entity> e1 = std::make_shared<Entity>();
		//智能指针的好处是防止delete遗忘
		e0 = e1;//只有shared_ptr可以进行赋值
		e00 = e1;
		//std::unique_ptr<Entity> e1 = e;//invalid
	}
	//在括号外e1已经被delete，因为赋值给了另一个生存域更大的shared_ptr类型e0，此处它们指向的Entity对象不会被销毁
	//weak_ptr可以被shared_ptr赋值，但是不能改变它指向的对象的生存域，该对象生存域由shared_ptr决定
}
#endif

#if 0
class String
{
private:
	char* m_Buffer;
	unsigned int m_Size;
public:
	String(const char* string)
	{
		m_Size = strlen(string);
		m_Buffer = new char[m_Size + 1];
		strcpy_s(m_Buffer, m_Size + 1, string);
		m_Buffer[m_Size] = 0;//手动将字符串的最后一个字符设置为\0，确保字符串正确结束。
	}
	~String()
	{
		delete[] m_Buffer;
	}
	String(const String& other)
		:m_Size(other.m_Size)
	{
		m_Buffer = new char[m_Size + 1];
		strcpy_s(m_Buffer, m_Size + 1, other.m_Buffer);
		cout << "Copied String!" << endl;
	}
	friend std::ostream& operator<<(std::ostream& stream, const String& string);
};
std::ostream& operator<<(std::ostream& stream, const String& string)
{
	stream << string.m_Buffer;
	return stream;
}
void PrintString(String string)
{
	cout << string << endl;
}
int main()
{
	String string("Hello World");
	String another_string = string;
	PrintString(string);
	PrintString(another_string);
	return 0;
}
#endif

#if 0
class Entity
{
public:
	int x;
	void Print() const
	{
		cout << "Hello" << endl;
	}
};
class ScopedPtr
{
private:
	Entity* m_ptr;
public:
	ScopedPtr(Entity* e)
		:m_ptr(e)
	{
	}
	~ScopedPtr()
	{
		delete m_ptr;
	}
	Entity* operator->()//重载->运算符，使得ScopedPtr对象可以像普通指针一样使用成员访问运算符来访问Entity对象的成员函数。
	{
		return m_ptr;
	}
};
int main()
{
	ScopedPtr scopedptr = new Entity();
	scopedptr->Print();
	return 0;
}
#endif

#if 0
struct Vector3
{
	float x, y, z;

};
int main()
{
	int offset = (int)&((Vector3*)nullptr)->y;
	cout << &((Vector3*)nullptr)->y << endl;
	cout << offset << endl;
	return 0;
}
#endif

#if 0
struct Vertex
{
	float x, y, z;
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex)
{
	stream << vertex.x << "," << vertex.y << "," << vertex.z;
	return stream;
}

int main()
{
	std::vector<Vertex> vertices;
	vertices.push_back({ 1, 2, 3 });
	vertices.push_back({ 4, 5, 6 });
	for (int i = 0; i < vertices.size();i++)
	{
		cout << vertices[i] << endl;
	}
	
	vertices.erase(vertices.begin()+1);

	for (Vertex& v : vertices)
	{
		cout << v << endl;
	}
	return 0;
}
#endif

#if 0
struct Vertex
{
	float x, y, z;
	Vertex(float x, float y, float z)//构造函数必须有，否则下面无法使用push_back等创建语句
		:x(x), y(y), z(z)
	{
	}
	Vertex(const Vertex& other)
		:x(other.x), y(other.y), z(other.z)
	{
		cout << "Copied Vertex!" << endl;
	}

};

int main()
{
	std::vector<Vertex> vertices;
	vertices.reserve(3);
	vertices.push_back({ 1, 2, 3 });
	vertices.push_back({ 4, 5, 6 });
	vertices.push_back({ 7, 8, 9 });
	//每加入一个新元素，检查容量，如果容量不够则销毁并重新分配空间，旧的元素被复制到新的空间中，最后新元素被添加到新的空间中
	
	vertices.emplace_back(1, 2, 3);
	vertices.emplace_back(4, 5, 6);
	vertices.emplace_back(7, 8, 9);
	//如果使用emplace_back()，则直接在stack上构造新元素，避免了不必要的复制和移动操作，提高了性能	
	return 0;
}
#endif

/*int main()
{
	int a = glfwInit();
	return 0;
}*/
 