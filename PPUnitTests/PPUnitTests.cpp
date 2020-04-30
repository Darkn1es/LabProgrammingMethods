#include "pch.h"
#include "CppUnitTest.h"
#include "..\PP\Model.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PPUnitTests
{
	TEST_CLASS(PPUnitTests)
	{
	public:

		TEST_METHOD(GetHashTest)
		{
			Transport t;

			t.type = TRAIN;
			t.speed = 5;
			t.length = 10;
			t.cargoWeight = 1;
			t.count = 1;

			Assert::IsTrue(getHash(t) == 16);
		}

		TEST_METHOD(GetTravelTimeTest)
		{
			Transport t;

			t.type = TRAIN;
			t.speed = 5;
			t.length = 10;
			t.cargoWeight = 1;
			t.count = 1;

			Assert::IsTrue(getTravelTime(t) == 2);
		}

		TEST_METHOD(ShipTypeToStringTest)
		{
			Assert::IsTrue("TOW" == shipTypeToString(ShipType::TOW));
		}

		TEST_METHOD(CompareTest)
		{
			Transport t1;

			t1.type = TRAIN;
			t1.speed = 5;
			t1.length = 10;
			t1.cargoWeight = 1;
			t1.count = 1;

			Transport t2;

			t2.type = TRAIN;
			t2.speed = 3;
			t2.length = 11;
			t2.cargoWeight = 1;
			t2.count = 1;

			Assert::IsTrue(compare(t1, t2) == false);

		}

		TEST_METHOD(SortTest)
		{
			string inputPath = "../../Utility/inputArray2.txt";
			ifstream infile(inputPath);

			vector<Transport> hasharray[MAXHASH];

			readFile(infile, hasharray);

			infile.close();

			sort(hasharray);
			Assert::IsTrue(getTravelTime(hasharray[14][0]) == 2, L"Assert 1");
			Assert::IsTrue(getTravelTime(hasharray[14][1]) == 3, L"Assert 2");
		}

		TEST_METHOD(ReadFileTest)
		{
			string inputPath = "../../Utility/inputArray1.txt";
			ifstream infile(inputPath);

			vector<Transport> hasharray[MAXHASH];

			readFile(infile, hasharray);
			infile.close();

			Transport t1 = hasharray[12][0];
			Assert::IsTrue(t1.type == PLANE, L"Plane Assert 1");

			Assert::IsTrue(t1.speed == 1, L"Plane Assert 2");
			Assert::IsTrue(t1.length == 2, L"Plane Assert 3");
			Assert::IsTrue(t1.cargoWeight == 3, L"Plane Assert 4");
			Assert::IsTrue(t1.range == 4, L"Plane Assert 5");
			Assert::IsTrue(t1.capacity == 5, L"Plane Assert 6");

			Transport t2 = hasharray[19][0];

			Assert::IsTrue(t2.type == TRAIN, L"Train Assert 1");

			Assert::IsTrue(t2.speed == 6, L"Train Assert 2");
			Assert::IsTrue(t2.length == 36, L"Train Assert 3");
			Assert::IsTrue(t2.cargoWeight == 8, L"Train Assert 4");
			Assert::IsTrue(t2.count == 9, L"Train Assert 5");




		}

		TEST_METHOD(WriteFileWithMissingTypeTest)
		{
			string inputPath = "../../Utility/inputArray1.txt";
			string outPath = "../../Utility/outputArray1.txt";

			ifstream infile(inputPath);
			ofstream output(outPath);


			vector<Transport> hasharray[MAXHASH];
			readFile(infile, hasharray);
			infile.close();
			writeToFile(output, hasharray, TRAIN);
			output.close();

			ifstream checkfile(outPath);
			std::stringstream buffer;
			buffer << checkfile.rdbuf();
			string result = buffer.str();

			string ideal = "Type of transport: PLANE\nMax capacity is 5\nMax range is 4\nDistance is 2\nMax speed is 1\nCargo weight is 3\nTravel time is 2\n\nThere are 1 transports\n";

			Assert::AreEqual(ideal, result);
		}




	};
}
