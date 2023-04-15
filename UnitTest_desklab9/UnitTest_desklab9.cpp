#include "pch.h"
#include "CppUnitTest.h"
#include "../desk_lab9/desk_lab9.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestdesklab9
{
	TEST_CLASS(UnitTestdesklab9)
	{
	public:
		
		 TEST_METHOD(TestMethod1)
        {
            string fname = "test_graph.txt";
            ofstream file(fname);
            file << "4 4\n1 2\n1 3\n2 3\n3 4\n";
            file.close();
            initGraph(fname);
            Assert::AreEqual(4, vertices);
            Assert::AreEqual(4, edges);

            for (int i = 0; i < vertices; i++) {
                Assert::IsNotNull(incidence[i]);
                Assert::IsNotNull(adjacency[i]);
                Assert::IsNotNull(adjacency2[i]);
            }
        }
        TEST_METHOD(TestMethod2)
        {
            string line = "1 2";
            int lineNumber = 0;
            makIncidenceMat(line, lineNumber);
            Assert::AreEqual(-1, incidence[0][lineNumber]);
            Assert::AreEqual(1, incidence[1][lineNumber]);
        }

        TEST_METHOD(TestMethod3)
        {
            adjacency[0][0] = 0;
            adjacency[0][1] = 0;
            adjacency[1][0] = 0;
            adjacency[1][1] = 0;

            makAdjacencyMat("1 2");
            makAdjacencyMat("2 1");
            makAdjacencyMat("2 2");

            Assert::AreEqual(0, adjacency[0][0]);
            Assert::AreEqual(1, adjacency[0][1]);
            Assert::AreEqual(1, adjacency[1][0]);
            Assert::AreEqual(1, adjacency[1][1]);
        }
        TEST_METHOD(TestMethod4) {
            const int vertices = 1;
            vector<vector<int>> adjacency2 = { {0} };
            ostringstream out;
            streambuf* coutbuf = cout.rdbuf();
            cout.rdbuf(out.rdbuf());
            funBFS(1);
            string expectedOutput = "| vershyna | Nomer BFS | cherha \n| v1       | 1         | 1\n| v2       | 2         | 1 2 \n| v3       | 3         | 1 2 3 \n| v4       | 4         | 3 4 \n";
            Assert::AreEqual(expectedOutput, out.str());
            // Clean
            cout.rdbuf(coutbuf);
        }
	};
}
