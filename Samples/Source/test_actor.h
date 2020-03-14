#include "Object/object.h"

#include <string>
#include <vector>
#include "Actors/actor.h"

namespace Ming3D
{
	class TestClass
	{
	public:
		int mTestValue = 1;

		~TestClass()
		{
			
		}
	};

	class TestActor : public Actor
	{
		DEFINE_CLASS(Ming3D::TestActor, Ming3D::Actor)
	public:
        int TestPropertyInt = 3;
        float TestPropertyFloat = 3.42f;

		void IntBoolTestFunction(int a, bool b);

		void StringTestFunction(std::string a);

		void IntVectorTestFunction(std::vector<int> a);

		void IntPointerTestFunction(int* a);

		void ObjectTestFunction(TestClass a);

		static void InitialiseClass();
	};
}
