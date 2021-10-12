#include "MeshFileParser.h"

using namespace std;

vector<Triangle*> parseOffFile(const char* filename) {

	ifstream file;
    //vector<int> v_t;
    int v_t[2];
    //vector<float> vertice;
    float vertice[3];
    vector<Point> vertices;
    //vector<int> triangle;
    int triangle[3];
    vector<Triangle*> triangles;

	file.open(filename, ios::in);

    string text;
    getline(file, text);
    //cout << text << endl;
    while (text[0] == '#') {
        cout << text << endl;
        getline(file, text);
    }

    getline(file, text);
    istringstream iss (text);
    int edges;
    if (!(iss >> v_t[0] >> v_t[1] >> edges)) {cout << "Error Parsing number of vertex and triangles" << endl; };

    //for (int i = 0; i < 2; i++) {
    //    getline(file, text);
        //cout << text << endl;
        //v_t.push_back(stoi(text));
    //}
    
    for (int i = 0; i < v_t[0]; i++) {
        getline(file, text);
        istringstream iss(text);
        if (!(iss >> vertice[0] >> vertice[1] >> vertice[2])) { cout << "Error parsing vertices" << endl; };
        //cout << vertice[0] << " " << vertice[1] << " " << vertice[2] << endl;
        vertices.push_back(Point(vertice[0], vertice[1], vertice[2]));
    }

    int numberOfPoints;
    for (int i = 0; i < v_t[1]; i++) {
        getline(file, text);
        istringstream iss(text);
        if (!(iss >> numberOfPoints >> triangle[0] >> triangle[1] >> triangle[2])) { cout << "Error parsing triangles" << endl; };
        //cout << triangle[0] << " " << triangle[1] << " " << triangle[2] << endl;
        triangles.push_back(new Triangle(vertices[triangle[0]], vertices[triangle[1]], vertices[triangle[2]], Material(Vector({ 1,1,1 }), MaterialBehaviour::Diffuse)));

        /*for (int j = 0; j < 4; j++) {
            getline(file, text, ' ');
            triangle.push_back(stof(text));
        }
        //cout << triangle[1] << endl;
        //cout << vertices[triangle[1]].data << endl;
        triangles.push_back(new Triangle(vertices[triangle[1]], vertices[triangle[2]], vertices[triangle[3]], Material(Vector({ 1,1,1 }), MaterialBehaviour::Diffuse)));
        triangle.clear();*/
    }

    file.close();

    //cout << triangles.size() << endl;
    //cout << "Parse Done" << endl;

    return triangles;

}
