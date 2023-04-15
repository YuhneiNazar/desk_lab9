#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <stack>
#include <vector>
#include <queue>

using namespace std;

int** incidence;
int** adjacency;
int** adjacency2;
int vertices;
int edges;

void initGraph(string fname);
void makIncidenceMat(string line, int lineNumber);
void makAdjacencyMat(string line);
void funBFS(int index);

int main()
{
    char fname[] = "graph_01.txt";
    initGraph(fname);

    int index;
    cout << "Vvedit indeks: "; cin >> index;
    funBFS(index);

}

void funBFS(int index) {
    queue<int> q;
    vector<bool> visited(vertices, false);

    int vertex = index;
    int count = 1;

    visited[index - 1] = true;
    q.push(index);

    cout << "| vershyna | Nomer BFS | cherha \n";
    cout << "| " << "v" << index << "       | " << count++ << "         | " << index << endl;

    while (!q.empty()) {
        vertex = q.front() - 1;
        int vis = -1;

        for (int i = 0; i < vertices; i++) {
            if (adjacency2[vertex][i] == 1 && !visited[i]) {
                vis = i;
                break;
            }
        }

        if (vis != -1) {
            visited[vis] = true;
            q.push(vis + 1);
            cout << "| " << "v" << vis + 1 << "       | " << count++ << "         | ";
            vector<int> tempVec;
            while (!q.empty()) {
                tempVec.push_back(q.front());
                q.pop();
            }
            for (int i = 0; i < tempVec.size(); i++) {
                cout << tempVec[i] << " ";
                q.push(tempVec[i]);
            }
            cout << endl;
        }
        else {
            q.pop();
        }
    }
}


void initGraph(string fname) {
    ifstream input(fname);
    if (!input.is_open()) {
        cout << "Pomylka vidkryttya faylu " << fname << endl;
        return;
    }

    string line;
    getline(input, line);
    if (!line.empty()) {
        istringstream iss(line);
        iss >> vertices >> edges;
        incidence = new int* [vertices];
        adjacency = new int* [vertices];
        adjacency2 = new int* [vertices];
        for (int i = 0; i < vertices; i++) {
            incidence[i] = new int[edges];
            adjacency[i] = new int[vertices];
            adjacency2[i] = new int[vertices];
        }
    }
    else {
        cout << "Porozhniy vkhidnyy fayl" << endl;
        return;
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            adjacency[i][j] = 0;
            adjacency2[i][j] = 0;
        }
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < edges; j++) {
            incidence[i][j] = 0;
        }
    }

    int lineNumber = 0;
    while (getline(input, line)) {
        makIncidenceMat(line, lineNumber);
        makAdjacencyMat(line);
        lineNumber++;
    }

    input.close();
}

void makIncidenceMat(string line, int lineNumber) {

    int from = stoi(line.substr(0, line.find(" ")));
    int to = stoi(line.substr(line.find(" ") + 1));

    if (from == to) {
        incidence[from - 1][lineNumber] = 2;
    }
    else {
        incidence[from - 1][lineNumber] = -1;
        incidence[to - 1][lineNumber] = 1;
    }
}

void makAdjacencyMat(string line) {

    int from = stoi(line.substr(0, line.find(" ")));
    int to = stoi(line.substr(line.find(" ") + 1));
    adjacency[from - 1][to - 1]++;
    adjacency2[from - 1][to - 1] = 1;
    adjacency2[to - 1][from - 1] = 1;
}
