#include "pch.h"
#include "CppUnitTest.h"
#include "../OOP/Model.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TransportUnitTests
{
	TEST_CLASS(TransportUnitTests)
	{
	public:
		TEST_METHOD(ReadTransportFromFileTest)
		{
			string inputPath = "../../Utility/inputTransport.txt";
			ifstream infile(inputPath);

			Transport t;
			t.ReadTransportFromFile(infile);
			infile.close();

			Assert::IsTrue(t.GetSpeed() == 5, L"Assert 1");
			Assert::IsTrue(t.GetLength() == 4, L"Assert 2");
			Assert::IsTrue(t.GetCargoWeight() == 3, L"Assert 3");

		}

		TEST_METHOD(WriteTransportToFileTest)
		{
			string outPath = "../../Utility/outputTransport.txt";
			ofstream output(outPath);

			Transport t;

			t.SetSpeed(1);
			t.SetCargoWeight(2);
			t.SetLength(3);

			t.WriteTransportToFile(output);
			output.close();

			ifstream infile(outPath);
			std::stringstream buffer;
			buffer << infile.rdbuf();
			string result = buffer.str();

			string ideal = "Distance is 3\nMax speed is 1\nCargo weight is 2\nTravel time is 3\n\n";

			Assert::AreEqual(ideal, result);
		}

		TEST_METHOD(GetTravelTimeTest)
		{
			Transport t;
			t.SetLength(20);
			t.SetSpeed(4);
			Assert::IsTrue(t.GetTravelTime() == 5.00);

		}

		TEST_METHOD(CompareTest)
		{
			Transport t1;
			Transport t2;

			t1.SetLength(20);
			t1.SetSpeed(4);

			t2.SetLength(16);
			t2.SetSpeed(4);

			Assert::IsTrue(t1.Compare(&t2));
		}
	};

	TEST_CLASS(PlaneUnitTests)
	{
	public:
		TEST_METHOD(ReadTransportFromFileTest)
		{
			string inputPath = "../../Utility/inputPlane.txt";
			ifstream infile(inputPath);

			Plane t;
			t.ReadTransportFromFile(infile);
			infile.close();

			Assert::IsTrue(t.GetSpeed() == 5, L"Assert 1");
			Assert::IsTrue(t.GetLength() == 4, L"Assert 2");
			Assert::IsTrue(t.GetCargoWeight() == 3, L"Assert 3");
			Assert::IsTrue(t.GetRange() == 2, L"Assert 4");
			Assert::IsTrue(t.GetCapacity() == 1, L"Assert 5");

		}

		TEST_METHOD(WriteTransportToFileTest)
		{
			string outPath = "../../Utility/outputPlane.txt";
			ofstream output(outPath);

			Plane t;

			t.SetSpeed(1);
			t.SetCargoWeight(2);
			t.SetLength(3);
			t.SetRange(4);
			t.SetCapacity(5);

			t.WriteTransportToFile(output);
			output.close();

			ifstream infile(outPath);
			std::stringstream buffer;
			buffer << infile.rdbuf();
			string result = buffer.str();

			string ideal = "Type of transport: PLANE\nMax capacity is 5\nMax range is 4\nDistance is 3\nMax speed is 1\nCargo weight is 2\nTravel time is 3\n\n";

			Assert::AreEqual(ideal, result);
		}
	};

	TEST_CLASS(TrainUnitTests)
	{
	public:
		TEST_METHOD(ReadTransportFromFileTest)
		{
			string inputPath = "../../Utility/inputTrain.txt";
			ifstream infile(inputPath);

			Train t;
			t.ReadTransportFromFile(infile);
			infile.close();

			Assert::IsTrue(t.GetSpeed() == 5, L"Assert 1");
			Assert::IsTrue(t.GetLength() == 4, L"Assert 2");
			Assert::IsTrue(t.GetCargoWeight() == 3, L"Assert 3");
			Assert::IsTrue(t.GetCount() == 2, L"Assert 4");

		}

		TEST_METHOD(WriteTransportToFileTest)
		{
			string outPath = "../../Utility/outputTrain.txt";
			ofstream output(outPath);

			Train t;

			t.SetSpeed(1);
			t.SetCargoWeight(2);
			t.SetLength(3);
			t.SetCount(4);

			t.WriteTransportToFile(output);
			output.close();

			ifstream infile(outPath);
			std::stringstream buffer;
			buffer << infile.rdbuf();
			string result = buffer.str();

			string ideal = "Type of transport: TRAIN\nCount of train car is 4\nDistance is 3\nMax speed is 1\nCargo weight is 2\nTravel time is 3\n\n";

			Assert::AreEqual(ideal, result);
		}
	};

	TEST_CLASS(ShipUnitTests)
	{
	public:
		TEST_METHOD(ReadTransportFromFileTest)
		{
			string inputPath = "../../Utility/inputShip.txt";
			ifstream infile(inputPath);

			Ship t;
			t.ReadTransportFromFile(infile);
			infile.close();

			Assert::IsTrue(t.GetSpeed() == 5, L"Assert 1");
			Assert::IsTrue(t.GetLength() == 4, L"Assert 2");
			Assert::IsTrue(t.GetCargoWeight() == 3, L"Assert 3");
			Assert::IsTrue(t.GetDisplacement() == 2, L"Assert 4");
			Assert::IsTrue(t.GetShipType() == Ship::TOW, L"Assert 5");
		}

		TEST_METHOD(WriteTransportToFileTest)
		{
			string outPath = "../../Utility/outputShip.txt";
			ofstream output(outPath);

			Ship t;

			t.SetSpeed(1);
			t.SetCargoWeight(2);
			t.SetLength(3);
			t.SetDisplacement(4);
			t.SetShipType(Ship::TANKER);

			t.WriteTransportToFile(output);
			output.close();

			ifstream infile(outPath);
			std::stringstream buffer;
			buffer << infile.rdbuf();
			string result = buffer.str();

			string ideal = "Type of transport: SHIP\nDisplacement is 4\nType of ship is TANKER\nDistance is 3\nMax speed is 1\nCargo weight is 2\nTravel time is 3\n\n";

			Assert::AreEqual(ideal, result);
		}
	};

	TEST_CLASS(HashArrayUnitTests)
	{
	public:
		
		TEST_METHOD(WriteFileWithMissingTypeTest)
		{
			string inputPath = "../../Utility/inputArray1.txt";
			string outPath = "../../Utility/outputArray1.txt";

			ifstream infile(inputPath);
			ofstream output(outPath);


			HashArray* arr = new HashArray();
			arr->ReadFile(infile);
			infile.close();

			arr->WriteFile(output, typeid(Train));
			output.close();
			ifstream checkfile(outPath);
			std::stringstream buffer;
			buffer << checkfile.rdbuf();
			string result = buffer.str();

			string ideal = "Type of transport: PLANE\nMax capacity is 5\nMax range is 4\nDistance is 2\nMax speed is 1\nCargo weight is 3\nTravel time is 2\n\nThere are 1 transports\n";

			Assert::AreEqual(ideal, result);



		}

		TEST_METHOD(SortTest)
		{
			string inputPath = "../../Utility/inputArray2.txt";
			ifstream infile(inputPath);
			HashArray* arr = new HashArray();
			arr->ReadFile(infile);
			infile.close();
			Assert::IsTrue(arr->Conteiner[14][0]->GetTravelTime() == 3, L"Assert 1");
			Assert::IsTrue(arr->Conteiner[14][1]->GetTravelTime() == 2, L"Assert 2");

		}

	};
}
