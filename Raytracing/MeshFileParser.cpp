#include "MeshFileParser.h"

using namespace std;

vector<Triangle*> parseOffFile(const char* filename) {

	ifstream file;
    vector<int> v_t;
    vector<float> vertice;
    vector<Point> vertices;
    vector<int> triangle;
    vector<Triangle*> triangles;

	file.open(filename, ios::in);

    string text;
    getline(file, text);
    //cout << text << endl;
    while (text[0] == '#') {
        cout << text << endl;
        getline(file, text);
    }
    for (int i = 0; i < 2; i++) {
        getline(file, text, ' ');
        //cout << text << endl;
        v_t.push_back(stoi(text));
    }
    
    for (int i = 0; i < v_t[0]; i++) {
        for (int j = 0; j < 3; j++) {
            getline(file, text, ' ');
            //cout << text << endl;
            vertice.push_back(stof(text));
        }
        vertices.push_back(Point(vertice[0], vertice[1], vertice[2]));
        vertice.clear();
    }

    for (int i = 0; i < v_t[1]; i++) {
        for (int j = 0; j < 4; j++) {
            getline(file, text, ' ');
            triangle.push_back(stof(text));
        }
        //cout << triangle[1] << endl;
        //cout << vertices[triangle[1]].data << endl;
        triangles.push_back(new Triangle(vertices[triangle[1]], vertices[triangle[2]], vertices[triangle[3]], Material(Vector({ 1,1,0 }), MaterialBehaviour::Diffuse)));
        triangle.clear();
    }

    file.close();

    //cout << triangles.size() << endl;
    //cout << "Parse Done" << endl;

    return triangles;

}
